# Modified Tic-Tac-Toe

[![Maven Version](https://img.shields.io/badge/Maven-Latest-c71a36?logo=apachemaven&logoColor=c71a36)](https://maven.apache.org/)
[![JDK Version](https://img.shields.io/badge/OpenJDK-17-000000?logo=openjdk&logoColor=000000)](https://openjdk.org/)

A game based on the classic Tic-Tac-Toe with modifications to add a third player.

## Modifications

- The jobs of the first two players are the same as the original. They mark (or occupy) tiles in the board until one of
  them forms a pattern and wins.

  The following are the patterns to form to win the game:

  <table>
    <tr>
      <th align="center">Left Vertical Line</th>
      <th align="center">Right Diagonal Line</th>
      <th align="center">Left Diagonal Line</th>
      <th align="center">Right Vertical Line</th>
    </tr>
    <tr>
      <td>
        <table>
          <tr>
            <th align="center">4</th>
            <td align="center">X</td>
            <td></td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <th align="center">3</th>
            <td align="center">X</td>
            <td></td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <th align="center">2</th>
            <td align="center">X</td>
            <td></td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <th align="center">1</th>
            <td align="center">X</td>
            <td></td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <td></td>
            <th align="center">1</th>
            <th align="center">2</th>
            <th align="center">3</th>
            <th align="center">4</th>
          </tr>
        </table>
      </td>
      <td>
        <table>
          <tr>
            <th align="center">4</th>
            <td></td>
            <td></td>
            <td></td>
            <td align="center">X</td>
          </tr>
          <tr>
            <th align="center">3</th>
            <td></td>
            <td></td>
            <td align="center">X</td>
            <td></td>
          </tr>
          <tr>
            <th align="center">2</th>
            <td></td>
            <td align="center">X</td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <th align="center">1</th>
            <td align="center">X</td>
            <td></td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <td></td>
            <th align="center">1</th>
            <th align="center">2</th>
            <th align="center">3</th>
            <th align="center">4</th>
          </tr>
        </table>
      </td>
      <td>
        <table>
          <tr>
            <th align="center">4</th>
            <td align="center">X</td>
            <td></td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <th align="center">3</th>
            <td></td>
            <td align="center">X</td>
            <td></td>
            <td></td>
          </tr>
          <tr>
            <th align="center">2</th>
            <td></td>
            <td></td>
            <td align="center">X</td>
            <td></td>
          </tr>
          <tr>
            <th align="center">1</th>
            <td></td>
            <td></td>
            <td></td>
            <td align="center">X</td>
          </tr>
          <tr>
            <td></td>
            <th align="center">1</th>
            <th align="center">2</th>
            <th align="center">3</th>
            <th align="center">4</th>
          </tr>
        </table>
      </td>
      <td>
        <table>
          <tr>
            <th align="center">4</th>
            <td></td>
            <td></td>
            <td></td>
            <td align="center">X</td>
          </tr>
          <tr>
            <th align="center">3</th>
            <td></td>
            <td></td>
            <td></td>
            <td align="center">X</td>
          </tr>
          <tr>
            <th align="center">2</th>
            <td></td>
            <td></td>
            <td></td>
            <td align="center">X</td>
          </tr>
          <tr>
            <th align="center">1</th>
            <td></td>
            <td></td>
            <td></td>
            <td align="center">X</td>
          </tr>
          <tr>
            <td></td>
            <th align="center">1</th>
            <th align="center">2</th>
            <th align="center">3</th>
            <th align="center">4</th>
          </tr>
        </table>
      </td>
    </tr>
    <tr>
      <td align="center">(1,1), (1,2), (1,3), (1,4)</td>
      <td align="center">(1,1), (2,2), (3,3), (4,4)</td>
      <td align="center">(1,4), (2,3), (3,2), (4,1)</td>
      <td align="center">(4,1), (4,2), (4,3), (4,4)</td>
    </tr>
  </table>

- The third player will be remove marks (or stealing) after the two players' turn. They win if they prevent both players
  from forming a pattern.

## Compiling

```shell
mvn compile
```

## Running

```shell
mvn exec:java
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

- Discrete Structures (CCDSTRU)
- Academic Year 2024-2025
- Year 1 (Undergraduate), Term 2
- Machine Project (MP)
