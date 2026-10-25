# BIG_INT_CPP

BIG_INT_CPP is a C++ project that implements a `BigInt` type for working with large integers. It includes a small example program and tests. CMake builds the project, and CTest runs the tests.

This guide is for Windows users who are new to C++ or CMake. Follow one compiler setup below; you do not need to install every compiler.

## What you need

- **Windows 10 or later**, 64-bit.
- **CMake 4.3.3 or newer.** CMake reads the project build instructions and generates build files for your compiler.
- **One C++ compiler toolchain** (compiler plus its build tools). The configurations checked for this project are:

  | Toolchain | Notes |
  | --- | --- |
  | MinGW GCC 6.x | Use the terminal where your MinGW compiler and `mingw32-make` are available. |
  | MSYS2 UCRT64 GCC 16.x | Recommended MinGW setup for a new MSYS2 installation. |
  | MSVC from Visual Studio | Install the C++ workload and use a Visual Studio Developer PowerShell. |

  These are configurations checked for this project, not a promise that every compiler version or distribution behaves identically.
- **Git**, only if you need to download the source using the command below. You can also download the repository as a ZIP.

The project has no additional third-party C++ library or test-framework dependencies.

## Get the source code

If Git is installed, open PowerShell or your chosen toolchain terminal and run:

```powershell
git clone https://github.com/Kunsh2301/BIG_INT_CPP.git
cd BIG_INT_CPP
```

If you downloaded a ZIP instead, extract it and open a terminal in the extracted project folder. The commands below must be run from the folder containing `CMakeLists.txt`.

## Build and test with MSVC

### Install and check the tools

1. Install Visual Studio and select the **Desktop development with C++** workload in the Visual Studio Installer. This installs MSVC, the Windows SDK, and the Visual Studio build tools.
2. Install CMake 4.3.3 or newer and make sure `cmake` is available on your `PATH`.
3. Open **Developer PowerShell for Visual Studio** from the Start menu. This sets up the MSVC environment for the terminal.
4. Check that CMake is available:

```powershell
cmake --version
```

The Visual Studio C++ workload provides the compiler. If you want to check it as well, run `cl` in Developer PowerShell; the compiler version and usage text should appear.

### Configure and build

Run these commands from the project folder:

```powershell
cmake -S . -B build-msvc -A x64
cmake --build build-msvc --config Debug
```

The first command creates a separate `build-msvc` folder and configures a 64-bit Visual Studio build. The second compiles the library, example program, and tests in Debug mode.

### Run the example and tests

```powershell
.\build-msvc\Debug\BIG_INT.exe
ctest --test-dir build-msvc -C Debug --output-on-failure
```

The first command runs the interactive example. Enter two whole numbers when prompted to see arithmetic, comparisons, assignment, unary, increment/decrement, and input/output operators demonstrated. The second command runs the tests and prints details if one fails.

## Build and test with MinGW GCC

There are two checked MinGW configurations: an existing MinGW GCC 6.x installation, and GCC 16.x in the MSYS2 UCRT64 environment. Use the instructions for the setup you have.

### Option A: Existing MinGW GCC 6.x installation

Open the terminal where MinGW is configured. It must be able to find both `g++` and `mingw32-make`. Check them, along with CMake:

```bash
g++ --version
mingw32-make --version
cmake --version
```

If a command is not found, add the corresponding compiler/build-tool and CMake locations to `PATH`, or use the terminal supplied with your MinGW installation. Run the build commands below from the project folder in that terminal.

### Option B: MSYS2 UCRT64 with GCC 16.x

1. Install [MSYS2](https://www.msys2.org/).
2. Open the **MSYS2 UCRT64** terminal from the Start menu. Do not use the MSYS, MINGW64, or plain Windows PowerShell terminal for these commands.
3. Install the compiler and build tools:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make mingw-w64-ucrt-x86_64-cmake git
```

4. Check the tools:

```bash
g++ --version
mingw32-make --version
cmake --version
```

If you already cloned the repository in Windows, navigate to its folder from UCRT64. For example, `C:\Users\YourName\Documents\BIG_INT_CPP` is `/c/Users/YourName/Documents/BIG_INT_CPP` in MSYS2. If you still need to download it, clone it in the UCRT64 terminal:

```bash
git clone https://github.com/Kunsh2301/BIG_INT_CPP.git
cd BIG_INT_CPP
```

Confirm you are in the project folder by checking that it contains `CMakeLists.txt`:

```bash
ls
```

### Configure and build

Run these commands from the project folder in the MinGW or UCRT64 terminal:

```bash
cmake -S . -B build-mingw -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build-mingw
```

The first command tells CMake to use MinGW Makefiles and creates a Debug build in `build-mingw`. The second compiles the project.

### Run the example and tests

```bash
./build-mingw/BIG_INT.exe
ctest --test-dir build-mingw --output-on-failure
```

The first command runs the interactive example. Enter two whole numbers when prompted to see arithmetic, comparisons, assignment, unary, increment/decrement, and input/output operators demonstrated. The second command runs the tests and prints details if one fails.

## A few useful notes

- Keep separate build folders for different compilers, as shown above. CMake stores the selected compiler and build system in each folder; do not reuse one compiler's build folder for another.
- After changing source files, run the build command again. After changing CMake settings, rerun the configure command (the first command in the relevant section).
- CTest currently registers one test named `BIG_INT_TESTS`. It runs the project's constructor, comparison, arithmetic, assignment, input/output, and unary-operator test functions.
- If CMake reports that it cannot find a compiler or Make, check that you opened the correct terminal and that the required tools are on `PATH`.
