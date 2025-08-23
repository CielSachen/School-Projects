# Convex Hull

[![CMake Version](https://img.shields.io/badge/CMake-%3E%3D3.15%20%3C%3D4.1-064f8c?logo=cmake&logoColor=064f8c)](https://cmake.org/)
![C Version](https://img.shields.io/badge/C-99-a8b9cc?logo=c&logoColor=a8b9cc)

A program that finds the convex hull from a set of points on a Cartesian plane. Two implementations of the program are
available: a slow and a fast implementation. The slow implementation uses the selection sort algorithm to sort the
points. While the fast implementation uses the heap sort algorithm. The points are parsed from a readable text file, and
the convex hull points are written to another text file.

## Compilation

Generate the project's build system:

```shell
cmake -B ./build/
```

Build the project:

```shell
cmake --build ./build/
```

## Usage

### Slow Implementation

MacOS and Linux:

```shell
./bin/convex-hull-slow
```

Windows:

```pwsh
.\bin\convex-hull-slow.exe
```

### Fast Implementation

MacOS and Linux:

```shell
./bin/convex-hull-fast
```

Windows:

```pwsh
.\bin\convex-hull-fast.exe
```

---

<img
  alt="DLSU Seal"
  height="125px"
  src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png"
/>
<img
  alt="CCS Logo"
  height="125px"
  src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png"
/>

## De La Salle University (DLSU)

- Data Structures and Algorithms (CCDSALG)
- Academic Year 2024-2025
- Year 1 (Undergraduate), Term 3
- Major Course Output 1 (MCO1)
