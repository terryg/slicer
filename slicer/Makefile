VENV ?= ../_venv
CONAN = $(VENV)/bin/conan
SETUP_STAMP = .slicer.setup.stamp
JOBS = -j$(echo "$(nproc) / 2" | bc)
BUILD_TYPE ?= Debug

.PHONY: setup lint build test clean

all: setup lint build;

CONAN_ARGS = -s compiler=clang -s compiler.version=18 -s build_type=$(BUILD_TYPE)

$(SETUP_STAMP): conanfile.py CMakeLists.txt
	$(CONAN) install -of _build $(CONAN_ARGS) -b missing conanfile.py
	cmake -S . -B _build \
				--preset conan-debug \
        -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
        -DCTEST_OUTPUT_ON_FAILURE=True
	touch $(SETUP_STAMP)

setup: $(SETUP_STAMP);

lint: setup;

build: setup
	$(MAKE) $(JOBS) -C _build

test:
	$(MAKE) $(JOBS) -C _build test

clean:
	rm -rf $(SETUP_STAMP)
	rm -rf _build
