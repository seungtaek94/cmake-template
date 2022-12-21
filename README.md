# cmake-tamplate
Simple cmake template for C++ shared library projects with google-test.


## Build Status
| System    | Debug                                                                                                                | Release                                                                                                                |
|-----------|----------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------|
| win-x64   | ![Build Status](https://github.com/seungtaek94/cmake-template/actions/workflows/build_win-x64_debug.yml/badge.svg)   | ![Build Status](https://github.com/seungtaek94/cmake-template/actions/workflows/build_win-x64_release.yml/badge.svg)   |
| linux-x64 | ![Build Status](https://github.com/seungtaek94/cmake-template/actions/workflows/build_linux-x64_debug.yml/badge.svg) | ![Build Status](https://github.com/seungtaek94/cmake-template/actions/workflows/build_linux-x64_release.yml/badge.svg) |

## Requirements

- cmake 3.16 or higher
- C++17 compiler
- `MSVC 16.xx(Visual Studio 2019)` for windows

## Build and Test
### Windows
```bash
# Clone the repository
git clone https://github.com/seungtaek94/cmake-template.git
cd cmake-template

# Generate build files
cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug -S .\ -B .\build

# Build 
cmake --build .\build --config Debug --target MyLib
cmake --build .\build --config Debug --target MyTests

# Run tests
cd .\RESULT\win-x64\Debug
.\test_MyLib.exe
```

### Linux

```bash
# Clone the repository
git clone https://github.com/seungtaek94/cmake-template.git
cd cmake-template

# Generate build files  
cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./build 

# Build
cmake --build ./build --config Debug --target MyLib
cmake --build ./build --config Debug --target MyTests

# Run tests
cd ./RESULT/linux-x64/Debug
./test_MyLib
```

## Citation
```bibtex
  @misc{seungtaek94 cmake-template,
    author = {Seungtaek Kim},
    title = {cmake-template},
    year = {2022},
    howpublished = {\url{https://github.com/seungtaek94/cmake-template},
  }
```