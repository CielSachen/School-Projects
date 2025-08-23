/*-
 * Modified Tic-Tac-Toe has modifications to add a third player.
 * Copyright (C) 2025  Raphael Panaligan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

package cielsachen.tictactoe;

import java.util.Set;
import java.util.stream.Collectors;

/** Represents the board where the game is "played." */
public class Board {
    /**
     * The positions on the board.
     * <p>
     * This implements the set <b>P</b>.
     */
    public static final Set<Position> POSITIONS = Set.of(
            new Position(1, 1), new Position(1, 2), new Position(1, 3), new Position(1, 4),
            new Position(2, 1), new Position(2, 2), new Position(2, 3), new Position(2, 4),
            new Position(3, 1), new Position(3, 2), new Position(3, 3), new Position(3, 4),
            new Position(4, 1), new Position(4, 2), new Position(4, 3), new Position(4, 4));
    /** The flattened coordinates of the positions on the board. */
    public static final Set<Integer> POSITION_COORDINATES = Board.POSITIONS
            .stream()
            .map(Position::flatten)
            .collect(Collectors.toSet());

    /**
     * The maximum number of columns the board can have.
     * <p>
     * This is defined by the greatest integer in the set <b>A</b>.
     */
    public static final int MAX_COLUMN_COUNT = 4;
    /**
     * The maximum number of rows the board can have.
     * <p>
     * This is defined by the greatest integer in the set <b>A</b>.
     */
    public static final int MAX_ROW_COUNT = 4;

    /**
     * Prints the board in an ASCII table format with labeled rows and columns.
     *
     * @param unoPositions  The positions occupied by Uno.
     * @param tresPositions The positions occupied by Tres.
     */
    public void print(Set<Position> unoPositions, Set<Position> tresPositions) {
        for (int rowNum = Board.MAX_ROW_COUNT; rowNum >= 0; rowNum--) {
            System.out.print("  ");

            for (int colNum = 1; colNum <= Board.MAX_COLUMN_COUNT; colNum++) {
                System.out.print("+---");

                if (colNum == Board.MAX_COLUMN_COUNT) {
                    System.out.println("+");
                }
            }

            for (int colNum = 0; colNum <= Board.MAX_COLUMN_COUNT; colNum++) {
                if (rowNum == 0) {
                    System.out.print("  ");

                    if (colNum > 0) {
                        System.out.print(colNum);

                        if (colNum == Board.MAX_COLUMN_COUNT) {
                            System.out.println();
                        } else {
                            System.out.print(" ");
                        }
                    }
                } else if (colNum == 0) {
                    System.out.print(rowNum + " ");
                } else {
                    Position pos = new Position(colNum, rowNum);

                    if (unoPositions.contains(pos)) {
                        System.out.print("| 1 ");
                    } else if (tresPositions.contains(pos)) {
                        System.out.print("| 3 ");
                    } else {
                        System.out.print("|   ");
                    }

                    if (colNum == Board.MAX_COLUMN_COUNT) {
                        System.out.println("|");
                    }
                }
            }
        }

        System.out.println();
    }
}
