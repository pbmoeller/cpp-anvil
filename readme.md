[![cpp-anvil Version v0.1.0](https://img.shields.io/badge/cpp--anvil-v0.1.0-green)](https://github.com/pbmoeller/cpp-anvil)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://github.com/pbmoeller/cpp-anvil/blob/main/LICENSE)

# cpp-anvil

cpp-anvil is a cross-platform C++ library for reading and writing Minecraft NBT data and Anvil files.

## Features

- Read and write Minecraft Anvil region files (`.mca`)
- Full support for NBT (Named Binary Tag) data, including compression (zlib)
- C++20 standard, modern and type-safe API
- Cross-platform: Windows, Linux, macOS
- Unit tests using GTest

## Requirements

- C++20 compatible compiler
- CMake >= 3.24 (tested with 3.28.3)
- [zlib](https://zlib.net/) (for NBT compression)
- [GTest](https://github.com/google/googletest) (for running tests, optional)

## Building

Clone the repository and build with CMake and Ninja:

```bash
$ git clone https://github.com/pbmoeller/cpp-anvil.git
$ cd cpp-anvil
$ cmake -B out/build
$ cmake --build out/build
```

You can specify your preferred generator or build directory as needed.

## Running Tests

To build and run the unit tests (requires GTest):

```bash
$ cmake -B out/build -DCPPANVIL_BUILD_TESTS=ON
$ cmake --build out/build
```

## License

This project is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please open issues or pull requests on GitHub.

## Acknowledgements

- Minecraft and NBT format by Mojang
- zlib for compression
- GoogleTest for unit testing