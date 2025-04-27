# Modified Tic-Tac-Toe

A game based on the classic Tic-Tac-Toe, but with modifications to add a third player.

- The jobs of the first two players are the same as the original. They mark (or occupy) tiles in the board until one of them forms a pattern and wins. The following are the patterns to form to win:

  | 4   | **X** |     |     |     |
  | --- | ----- | --- | --- | --- |
  | 3   | **X** |     |     |     |
  | 2   | **X** |     |     |     |
  | 1   | **X** |     |     |     |
  |     | 1     | 2   | 3   | 4   |

  | 4   |       |       |       | **X** |
  | --- | ----- | ----- | ----- | ----- |
  | 3   |       |       | **X** |       |
  | 2   |       | **X** |       |       |
  | 1   | **X** |       |       |       |
  |     | 1     | 2     | 3     | 4     |

  | 4   | **X** |       |       |       |
  | --- | ----- | ----- | ----- | ----- |
  | 3   |       | **X** |       |       |
  | 2   |       |       | **X** |       |
  | 1   |       |       |       | **X** |
  |     | 1     | 2     | 3     | 4     |

  | 4   |     |     |     | **X** |
  | --- | --- | --- | --- | ----- |
  | 3   |     |     |     | **X** |
  | 2   |     |     |     | **X** |
  | 1   |     |     |     | **X** |
  |     | 1   | 2   | 3   | 4     |

- Meanwhile, the third player will be remove marks (or stealing) after the two players' turn. They win if they prevent both players from forming a pattern.

## Compilation

```bash
javac ./**/*.java
```

## Usage

> [!IMPORTANT]
> The working directory for the game is the `src/main/java` folder; therefore, you must run the following command inside of the `src/main/java` folder:
>
> ```bash
> cd ./src/main/java/
> ```

```bash
java cielsachen.ccdstru.Main
```

---

<img src="https://upload.wikimedia.org/wikipedia/en/thumb/c/c2/De_La_Salle_University_Seal.svg/2048px-De_La_Salle_University_Seal.svg.png" alt="DLSU Seal" height="125px"> <img src="https://www.dlsu.edu.ph/wp-content/uploads/2019/06/ccs-logo.png" alt="CCS Logo" height="125px">

## De La Salle University (Undergraduate)

This repository contains the source code of my group's machine project for **Discrete Structures** (Term 2, A.Y. 2024-25).
