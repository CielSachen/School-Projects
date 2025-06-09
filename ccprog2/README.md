# Simple Translator

A simple CLI-based translator application that takes in translation inputs to translate words. **Translations are not guaranteed to be accurate because of limitations, especially with longer sentences.** No bonus points features were added.

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

> [!WARNING]
> This CLI game uses UTF-8 characters, which Powershell (in Windows) does not fully support yet. To allow Powershell to display UTF-8 characters, run this script before running the game:
>
> ```pwsh
> $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
> ```

```bash
# For Linux systems:
./bin/simple_translator.out
# For macOS systems:
./bin/simple_translator
# For Windows systems:
./bin/simple_translator.exe
```

---

<img src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png" alt="DLSU Seal" height="125px"> <img src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png" alt="CCS Logo" height="125px">

## De La Salle University (Undergraduate)

This repository contains the source code of my machine project for **Programming with Data Structures** (Term 2, A.Y. 2024-25).
