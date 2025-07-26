[![cpp-anvil Version v0.1.0](https://img.shields.io/badge/cpp-anvil-v0.1.0-green)](https://github.com/pbmoeller/cpp-anvil)
[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://github.com/pbmoeller/cpp-anvil/LICENSE)

# cpp-anvil

cpp-anvil is a cross-platform C++ library for reading and writing Minecraft NBT data and Anvil files.

## Building the library

cpp-anvil requires a compiler that supports C++20 to build the library.

The library depends on zlib for compression and decompression of NBT data. You can install zlib using your package manager or download it from [zlib.net](https://zlib.net/).

To build the library, you can use CMake. Here are the steps to build the library:

```bash
$ git clone https://github.com/pbmoeller/cpp-anvil.git
$ cd cpp-anvil
$ cmake -B out/build
$ cmake --build out/build
```

