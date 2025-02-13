VENV ?= ../_venv
CONAN = $(VENV)/bin/conan
SETUP_STAMP = .slicer.setup.stamp
BUILD_TYPE ?= Debug

ifeq ($(BUILD_TYPE),Release)
  CONAN_PRESET = conan-release
else
  CONAN_PRESET = conan-debug
endif

.PHONY: setup build clean

all: setup build;

CONAN_ARGS = -s compiler=clang -s compiler.version=18 -s build_type=$(BUILD_TYPE)

$(SETUP_STAMP): conanfile.py CMakeLists.txt
	$(CONAN) install -of _build $(CONAN_ARGS) -b missing conanfile.py
	cmake -S . -B _build --preset $(CONAN_PRESET) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)
	touch $(SETUP_STAMP)

setup: $(SETUP_STAMP);

build: setup
	$(MAKE) -C _build

clean:
	rm -rf $(SETUP_STAMP)
	rm -rf _build
