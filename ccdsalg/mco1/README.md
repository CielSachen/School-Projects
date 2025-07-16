# Convex Hull

A program that finds the convex hull from a set of points on a Cartesian plane. The program is divided into two: a slow
and a fast version. The slow version uses the selection sort algorithm to sort the points, while the fast version uses
the heap sort algorithm.

## Compilation

Set up the platform-specific build process:

```bash
cmake -B ./build/ -S ./
```

Build and compile the libraries and the program:

```bash
cmake --build ./build --target all
```

## Usage

MacOS and Linux:

```bash
./bin/convex_hull_slow
./bin/convex_hull_fast
```

Windows:

```pwsh
.\bin\convex_hull_slow.exe
.\bin\convex_hull_fast.exe
```

---

<img 
  src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png"
  height="125px"
  width="125px"
  alt="DLSU Seal">
<img
  src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png"
  height="125px"
  width="125px"
  alt="CCS Logo">

## De La Salle University (Undergraduate)

This repository contains the source code of my group’s machine project for **Data Structures and Algorithms**
(Term 3, A.Y. 2024-25).
