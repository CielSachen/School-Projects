/*
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

package cielsachen.ccdstru;

import java.util.Set;
import java.util.stream.Collectors;

/**
 * The board where the game is played.
 * 
 * @implSpec This implementation is a singleton; only one instance of this class
 *           can exist.
 */
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
    public static final Set<Integer> POSITION_COORDINATES = Board.POSITIONS.stream().map(Position::flatten)
            .collect(Collectors.toSet());

    /**
     * The maximum number of columns the board can have.
     * <p>
     * This is defined by the greatest integer in the set <b>A</b>.
     */
    public static final int MAXIMUM_COLUMN_COUNT = 4;
    /**
     * The maximum number of rows the board can have.
     * <p>
     * This is defined by the greatest integer in the set <b>A</b>.
     */
    public static final int MAXIMUM_ROW_COUNT = 4;

    /** The singular instance of the {@code Board} class. */
    private static Board instance = null;

    /** Creates a new instance of the {@code Board} class. */
    private Board() {
    }

    /**
     * Gets the singular instance of the {@code Board} class.
     * <p>
     * This function creates a new instance if one does not already exist.
     * 
     * @return The instance of the {@code Board} class.
     */
    public static synchronized Board getInstance() {
        if (Board.instance == null) {
            Board.instance = new Board();
        }

        return Board.instance;
    }

    /**
     * Prints the board to {@code stdout} in an ASCII table format.
     * 
     * @param unoPositions  The positions that are occupied by Uno.
     * @param tresPositions The positions that are occupied by Tres.
     */
    public void print(Set<Position> unoPositions, Set<Position> tresPositions) {
        for (int rowNumber = Board.MAXIMUM_ROW_COUNT; rowNumber >= 0; rowNumber--) {
            System.out.print("  ");

            for (int columnNumber = 1; columnNumber <= Board.MAXIMUM_COLUMN_COUNT; columnNumber++) {
                System.out.print("+---");

                if (columnNumber == Board.MAXIMUM_COLUMN_COUNT) {
                    System.out.println("+");
                }
            }

            for (int columnNumber = 0; columnNumber <= Board.MAXIMUM_COLUMN_COUNT; columnNumber++) {
                if (rowNumber == 0) {
                    System.out.print("  ");

                    if (columnNumber > 0) {
                        System.out.print(columnNumber);

                        if (columnNumber == Board.MAXIMUM_COLUMN_COUNT) {
                            System.out.println();
                        } else {
                            System.out.print(" ");
                        }
                    }
                } else if (columnNumber == 0) {
                    System.out.print(rowNumber + " ");
                } else {
                    Position position = new Position(columnNumber, rowNumber);

                    if (unoPositions.contains(position)) {
                        System.out.print("| 1 ");
                    } else if (tresPositions.contains(position)) {
                        System.out.print("| 3 ");
                    } else {
                        System.out.print("|   ");
                    }

                    if (columnNumber == Board.MAXIMUM_COLUMN_COUNT) {
                        System.out.println("|");
                    }
                }
            }
        }

        System.out.println();
    }
}
