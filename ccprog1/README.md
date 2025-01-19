# Tides of Manila: A Merchant's Quest

A turn-based CLI-based game where you trade with various ethnic groups to become the most successful merchant in Manila. Your objective is to meet or exceed your profit target by the end of the month; otherwise, you will lose. The following are the bonus points features:

1. An upgradeable ship to increase the amount of cargo you can carry.
2. A random semi-realistic weather system that can derail your progress.

## Compilation

> [!TIP]
> Replace the `CC` (C compiler) value with the compiler of your choice.

### Windows

```bash
make CC=gcc windows
```

### macOS

> [!IMPORTANT]
> The Homebrew installed versions of gcc and GNU make are named `gcc-14` and `gmake`, respectively.

```bash
gmake CC=gcc-14 macos
```

## Usage

### Windows

> [!WARNING]
> This CLI game uses UTF-8 characters, which Powershell does not fully support yet. To allow Powershell to display UTF-8 characters, run this script before running the game:
>
> ```pwsh
> $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
> ```

```bash
.\a.exe
```

### macOS

```bash
./a.out
```

---

<img src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png" alt="DLSU Seal" height="125px"> <img src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png" alt="CCS Logo" height="125px">

## De La Salle University (Undergraduate)

This repository contains the source code of my machine project for **Logic Formulation and Introductory Programming** (Term 1, A.Y. 2024-25).
