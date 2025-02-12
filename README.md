# Slicer

Canonical mesh slicer using CGAL. Slices input mesh along Z-axis at
desired thickness (epsilon == 1e-6).

## Development

Install system dependencies for Linux (Ubuntu 24.04 LTS). Remove `gcc` for good measure.

```
$ sudo apt update && sudo apt upgrade -y
$ sudo apt install -y cmake clang clang-tidy curl
$ sudo apt remove gcc
```

Install `pyenv` and install 3.12.6 globally.

```
$ curl https://pyenv.run | bash
$ pyenv install 3.12.6
$ pyenv global 3.12.6
```
  
Clone this repository and then setup & build. Ensure `python3 --version` is 3.12.6

```
$ git clone https://github.com/terryg/slicer.git
$ cd slicer
$ python3 --version
Python 3.12.6
$ make setup
$ make build
$ make test
$ ./slicer/_build/slicer --help
```

Use `make clean` to build from scratch. Use `rm -rf ~/.conan2` to rebuild Conan packages.
  
## License

Copyright (c) 2025 Terry Lorber. See the [LICENSE](LICENSE).
