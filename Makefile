VENV ?= _venv
PYTHON = $(VENV)/bin/python3
PIP = $(VENV)/bin/pip
CONAN = $(VENV)/bin/conan

.PHONY: setup build clean

$(VENV)/bin/activate: ## Creates a Python virtual environment (venv)
	python3 -m venv $(VENV)
	$(PYTHON) -m pip install --upgrade pip
	$(PIP) install conan

setup: $(VENV)/bin/activate ## Setup to lint, build, and test
	$(CONAN) remote update conancenter --url="https://center2.conan.io"
	$(CONAN) profile detect --force
	$(MAKE) -C ./slicer setup

build:
	$(MAKE) -C ./slicer build

clean:
	$(MAKE) -C ./slicer clean
	rm -rf $(VENV)

