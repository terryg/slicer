from conan import ConanFile
from conan.tools.cmake import CMake


class Slicer(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("cgal/6.0.1")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

