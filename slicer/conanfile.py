from conan import ConanFile


class Slicer(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("cgal/6.0.1")
        self.requires("cxxopts/3.2.0")

