# TinyOrmQtDemo

**TinyOrmQtDemo** is a demonstration proof-of-concept application built with **Qt** and **TinyORM**.  
It showcases a basic integration of a Qt GUI with TinyORM models using modern C++ and CMake build tools.

---

## Features

- Simple Qt-based GUI  
- Demonstrates CRUD operations using TinyORM  
- Modern CMake and Conan2 integration  

---

## Prerequisites

- C++ compiler
- Windows 11 SDK
- [CMake](https://cmake.org/)
- [Conan2](https://conan.io/)

---

## Building the Project

1. **Install Conan2** if not already installed:

```
pip install conan
```

2. **Set up a Conan profile** for your compiler and environment:

```
conan profile detect
```

3. **Install dependencies** using Conan:

```
conan install . --build=missing
```

4. **Configure the project with CMake**:

```
cmake --preset conan-default
```

5. **Build the project**:

```
cmake --build --preset conan-release
```

6. The executable will be available in the `build` directory.

---

## License

This application is licensed under the **MIT License**.

### Third-party Dependencies

- [Qt](https://www.qt.io/) — LGPL 3.0  
- [TinyORM](https://github.com/fnc12/tinyorm) — MIT License
