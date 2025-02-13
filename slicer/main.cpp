#include <cxxopts.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
 
#include <CGAL/Polygon_mesh_slicer.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
 
#include <CGAL/AABB_halfedge_graph_segment_primitive.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits_3.h>
 
#include <iostream>
#include <list>
#include <string>
#include <vector>
 
typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef CGAL::Surface_mesh<K::Point_3>                        Mesh;
 
typedef std::vector<K::Point_3>                               Polyline_type;
typedef std::list<Polyline_type>                              Polylines;
 
typedef CGAL::AABB_halfedge_graph_segment_primitive<Mesh>     HGSP;
typedef CGAL::AABB_traits_3<K, HGSP>                          AABB_traits;
typedef CGAL::AABB_tree<AABB_traits>                          AABB_tree;
 
namespace PMP = CGAL::Polygon_mesh_processing;

static constexpr double EPSILON = 1e-6;

int main(int argc, char* argv[])
{
  cxxopts::Options options("slicer", "Slice a mesh at a given interval in Z.");

  options.add_options()
    ("h, help", "Show this help message and exit")
    ("t, thickness", "The z-interval in world units", cxxopts::value<double>()->default_value("0.1"))
    ("paths", "The path(s) to slice.", cxxopts::value<std::vector<std::string>>());

  options.positional_help("[FILE]...");

  options.parse_positional({"paths"});

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  if (result.count("paths") == 0) {
    std::cerr << "At least one filepath must be specified." << std::endl;
    return 1;
  }

  double thickness = result["thickness"].as<double>();

  if (thickness < 0.0) {
    std::cerr << "Thickness must be non-negative." << std::endl;
    return 1;
  }

  if (thickness < EPSILON) {
    std::cout << "Minimum thickness is " << EPSILON << " world units." << std::endl;
    thickness = EPSILON;
  }

  std::vector<std::string> paths = result["paths"].as<std::vector<std::string>>();

  for (const auto &inpath_str : paths) {
    Mesh mesh;
    if (!PMP::IO::read_polygon_mesh(inpath_str, mesh) || CGAL::is_empty(mesh) || !CGAL::is_triangle_mesh(mesh)) {
      std::cerr << "Invalid input -> " << inpath_str << std::endl;
      return 1;
    }
 
    AABB_tree tree(edges(mesh).first, edges(mesh).second, mesh);

    auto bbox = tree.bbox();
    double zmin = bbox.zmin();
    double zmax = bbox.zmax();

    CGAL::Polygon_mesh_slicer<Mesh, K> slicer_aabb(mesh, tree);

    Polylines polylines;

    for (double zindex = zmin + thickness;
         zindex < zmax;
         zindex = zindex + thickness) {
      slicer_aabb(K::Plane_3(0, 0, 1, zindex), std::back_inserter(polylines));
      std::cout << "At z = " << zindex << ", the slicer intersects "
                << polylines.size() << " polylines" << std::endl;
      polylines.clear();
    }

    mesh.clear();
  }

  return 0;
}
