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

import java.util.HashSet;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Set;

/** Represents the game's backend. */
public class Game {
    /**
     * The patterns of positions needed to be occupied for a player to win the game.
     * <p>
     * This implements the set <b>C</b>.
     */
    public static final Set<Set<Position>> WINNING_CONDITIONS = Set.of(
            Set.of(new Position(1, 1), new Position(1, 2), new Position(1, 3), new Position(1, 4)),
            Set.of(new Position(1, 1), new Position(2, 2), new Position(3, 3), new Position(4, 4)),
            Set.of(new Position(1, 4), new Position(2, 3), new Position(3, 2), new Position(4, 1)),
            Set.of(new Position(4, 1), new Position(4, 2), new Position(4, 3), new Position(4, 4)));

    /** The board where the game is being "played." */
    private Board board = new Board();
    /**
     * The positions on the board that are unoccupied.
     * <p>
     * This implements the set <b>F</b>.
     */
    private Set<Position> remainingBoardPositions;

    /**
     * The positions on the board occupied by Uno.
     * <p>
     * This implements the set <b>Uno</b>.
     */
    private Set<Position> unoPositions = new HashSet<>();
    /**
     * The positions on the board occupied by Dos.
     * <p>
     * This implements the set <b>Dos</b>.
     *
     * @apiNote This field was only added to keep consistency with the specifications. This will never be used, as Dos
     *          only takes away positions, never taking them in.
     */
    @SuppressWarnings("unused")
    private Set<Position> dosPositions = new HashSet<>();
    /**
     * The positions on the board occupied by Tres.
     * <p>
     * This implements the set <b>Tres</b>.
     */
    private Set<Position> tresPositions = new HashSet<>();

    /**
     * Whether the player will occupy or steal a position in the current turn.
     * <p>
     * This implements the element <b>turn</b>.
     */
    private boolean isOccupyingTurn = true;
    /**
     * Whether it's the player Uno's turn to play.
     * <p>
     * This implements the element <b>go</b>.
     */
    private boolean isUnoTurn = false;

    /**
     * Whether the game is over.
     * <p>
     * This implements the element <b>over</b>.
     */
    private boolean isOver = false;

    /**
     * Gets an integer input, corresponding to a position's coordinates on the board, from a player.
     *
     * @param scanner    The input scanner.
     * @param isStealing Whether the player will steal or occupy the position.
     * @return The position on the coordinates received from the user.
     */
    private Position getPositionInput(Scanner scanner, boolean isStealing) {
        Position pos;

        while (true) {
            System.out.print("Input a position's coordinates (XY): ");

            int givenCoords;

            try {
                givenCoords = scanner.nextInt();
            } catch (InputMismatchException exception) {
                scanner.nextLine();

                givenCoords = 0;
            }

            if (!Board.POSITION_COORDINATES.contains(givenCoords)) {
                System.out.println("Please input an existing position's coordinates.");

                continue;
            }

            pos = new Position(givenCoords / 10, givenCoords % 10);

            if (!isStealing && !this.remainingBoardPositions.contains(pos)) {
                System.out.println("Please input an unoccupied position's coordinates.");

                continue;
            } else if (isStealing && this.remainingBoardPositions.contains(pos)) {
                System.out.println("Please input an occupied position's coordinates.");

                continue;
            }

            break;
        }

        return pos;
    }

    /**
     * Updates a position to either be occupied by a player or returned to the board.
     * <p>
     * This implements the function <b>NextPlayerMove</b>(<i>pos</i> ∈ <b>P</b>).
     *
     * @param position The position to update.
     */
    private void updatePosition(Position pos) {
        if (this.isOccupyingTurn && this.isUnoTurn && this.remainingBoardPositions.contains(pos)) {
            this.unoPositions.add(pos);
            this.remainingBoardPositions.remove(pos);

            this.isOccupyingTurn = !this.isOccupyingTurn;
            this.isUnoTurn = !this.isUnoTurn;
        } else if (!this.isOccupyingTurn && (this.unoPositions.contains(pos) || this.tresPositions.contains(pos))) {
            if (this.unoPositions.contains(pos)) {
                this.unoPositions.remove(pos);
            } else {
                this.tresPositions.remove(pos);
            }

            this.remainingBoardPositions.add(pos);

            this.isOccupyingTurn = !this.isOccupyingTurn;
        } else if (this.isOccupyingTurn && !this.isUnoTurn && this.remainingBoardPositions.contains(pos)) {
            this.tresPositions.add(pos);
            this.remainingBoardPositions.remove(pos);

            this.isUnoTurn = !this.isUnoTurn;
        }
    }

    /**
     * Gets the proclamation of which player (if any) had won the game.
     * <p>
     * This implements the function <b>GameOver</b>(<i>over</i>).
     *
     * @return The proclamation of a winner.
     */
    private String getWinner() {
        if (this.isOver) {
            if (Game.WINNING_CONDITIONS.contains(this.unoPositions)) {
                return "Uno Wins";
            } else if (this.remainingBoardPositions.isEmpty()) {
                return "Dos Wins";
            } else if (Game.WINNING_CONDITIONS.contains(this.tresPositions)) {
                return "Tres Wins";
            }
        }

        return "No Winner";
    }

    /**
     * Runs the <b>game loop</b> responsible for allocating and repeating each player's turns until the game is over.
     */
    public void run() {
        var scanner = new Scanner(System.in);

        this.remainingBoardPositions = new HashSet<>(Board.POSITIONS);

        while (true) {
            this.isOver = Game.WINNING_CONDITIONS.stream().anyMatch((c) -> this.unoPositions.containsAll(c))
                    || Game.WINNING_CONDITIONS.stream().anyMatch((c) -> this.tresPositions.containsAll(c))
                    || this.remainingBoardPositions.isEmpty();

            this.board.print(this.unoPositions, this.tresPositions);

            if (this.isOver) {
                break;
            }

            if (this.isOccupyingTurn && this.isUnoTurn) {
                System.out.println("Uno's Turn");
            } else if (this.isOccupyingTurn && !this.isUnoTurn) {
                System.out.println("Tres' Turn");
            } else {
                System.out.println("Dos' Turn");
            }

            System.out.println();

            this.updatePosition(this.getPositionInput(scanner, !this.isOccupyingTurn));

            System.out.println();
        }

        System.out.println("Result: " + this.getWinner());

        scanner.close();
    }
}
