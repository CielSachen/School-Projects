# Tides of Manila

A turn-based game where you trade with various ethnic groups to become the most successful merchant in Manila. Your
primary goal to win the game will be meeting or exceeding your set profit target by the end of the month; otherwise, you
will lose.

## Compilation

Set up the platform-specific build process:

```bash
cmake -B ./build/ -S ./
```

Build and compile the libraries and the program:

```bash
cmake --build ./build/ --target all
```

## Usage

MacOS and Linux:

```bash
./bin/tides_of_manila
```

Windows:

> [!WARNING]
> This game uses UTF-8 characters, which the Windows terminal does not support by default. To display UTF-8 characters,
> run this script before running the game:
>
> ```pwsh
> $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
> ```

```pwsh
.\bin\tides_of_manila.exe
```

---

<img
  src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png"
  height="125px"
  width="125px"
  alt="DLSU Seal"
/>
<img
  src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png"
  height="125px"
  width="125px"
  alt="CCS Logo"
/>

## De La Salle University (Undergraduate)

This repository contains the source code of my machine project for **Logic Formulation and Introductory Programming**
(Term 1, A.Y. 2024-25).
