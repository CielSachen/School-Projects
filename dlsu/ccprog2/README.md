# Simple Translator

[![CMake Version](https://img.shields.io/badge/CMake-%3E%3D3.15%20%3C%3D4.1-064f8c?logo=cmake&logoColor=064f8c)](https://cmake.org/)
![C Version](https://img.shields.io/badge/C-99-a8b9cc?logo=c&logoColor=a8b9cc)

A translator program that creates and uses translation dictionaries to translate words. The translation dictionaries are
made through the CLI and exported for later use. Translations are done on words or sentences inputted via the CLI or a
readable text file. The program translates the words in sentences one-by-one, resulting in inaccurate sentence
translations. (This is a known limitation and intended behavior).

## Building

Generate the project's build system:

```shell
cmake -B ./build/
```

Build the project:

```shell
cmake --build ./build/
```

## Running

MacOS and Linux:

```shell
./bin/simple-translator
```

Windows:

> [!WARNING]
> This program uses UTF-8 characters, which the Windows terminal does not support by default. To display UTF-8
> characters, run this script before running the program:
>
> ```powershell
> $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
> ```

```powershell
.\bin\simple-translator.exe
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

- Programming with Data Structures (CCPROG2)
- Academic Year 2024-2025
- Year 1 (Undergraduate), Term 2
- Machine Project (MP)
