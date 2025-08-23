# Tides of Manila

[![CMake Version](https://img.shields.io/badge/CMake-%3E%3D3.15%20%3C%3D4.1-064f8c?logo=cmake&logoColor=064f8c)](https://cmake.org/)
![C Version](https://img.shields.io/badge/C-99-a8b9cc?logo=c&logoColor=a8b9cc)

A turn-based game where you trade with various ethnic groups to become the most successful merchant in Manila!

This game is set in the Manila region. More specifically, the settlements of Tondo, Manila, Pandakan, and Sapa. You will
be the captain of a ship that carries cargo that will be traded with these settlements.

## Features

- **Goal Setting** - The profit target will be set before the game starts. A month will be given to meet or exceed this,
  otherwise the game will be lost.
- **Progression** - The ship will be upgradeable up to four tiers. Each tier will increase the amount of cargo it can
  carry and update the home screen.
- **Economy** - Cargo can be bought and sold in each settlement, with the prices differing per settlement, per day.
- **Constraints** - Traveling to other settlements will move the day forward, and may cause a storm to form. Storms, if
  severe enough, may cause some cargo to be lost.
- **Quitting** - The game can be ended early if desired, and will be won if the profit target was already met or
  exceeded.

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
./bin/tides-of-manila
```

Windows:

> [!WARNING]
> This game uses UTF-8 characters, which the Windows terminal does not support by default. To display UTF-8 characters,
> run this script before running the game:
>
> ```powershell
> $OutputEncoding = [console]::InputEncoding = [console]::OutputEncoding = New-Object System.Text.UTF8Encoding
> ```

```powershell
.\bin\tides-of-manila.exe
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

- Logic Formulation and Introductory Programming (CCPROG1)
- Academic Year 2024-2025
- Year 1 (Undergraduate), Term 1
- Machine Project (MP)
