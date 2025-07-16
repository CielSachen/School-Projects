# Simple Translator

A translator program that creates and uses translation dictionaries to translate words. The program can translate
sentences by translating word-by-word, resulting in inaccurate sentence translations. (This is intended behavior).

## Compilation

Set up the platform-specific build process:

```bash
cmake -B ./build/ -S ./
```

Build and compile the libraries and the program:

```bash
cmake --build ./build --target simple_translator
```

## Usage

MacOS and Linux:

```bash
./bin/simple_translator
```

Windows:

> [!WARNING]
> This program uses UTF-8 characters, which the Windows terminal does not support by default. To display UTF-8
> characters, run this script before running the game:
>
> ```pwsh
> $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
> ```

```pwsh
.\bin\simple_translator.exe
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

This repository contains the source code of my machine project for **Programming with Data Structures** (Term 2, A.Y. 2024-25).
