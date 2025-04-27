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

import java.util.HashSet;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Set;

/**
 * The game's core functionality and mechanics.
 * 
 * @implSpec This implementation's instances will be executed in their own
 *           threads.
 */
public class Game implements Runnable {
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

    /** The thread to execute the instance of the {@code Game} class in. */
    private Thread gameThread;

    /** The board where the game is being "played." */
    private Board board = Board.getInstance();

    /**
     * The positions on the board that are unoccupied.
     * <p>
     * This implements the set <b>F</b>.
     */
    private Set<Position> remainingBoardPositions;

    /**
     * The positions on the board that are occupied by Uno.
     * <p>
     * This implements the set <b>Uno</b>.
     */
    private Set<Position> unoPositions = new HashSet<Position>();
    /**
     * The positions on the board that are occupied by Dos.
     * <p>
     * This implements the set <b>Dos</b>.
     * 
     * @apiNote This field was only added to keep consistency with the
     *          specifications. This will never be used, as Dos
     *          only takes away positions, never taking them in.
     */
    @SuppressWarnings("unused")
    private Set<Position> dosPositions = new HashSet<Position>();
    /**
     * The positions on the board that are occupied by Tres.
     * <p>
     * This implements the set <b>Tres</b>.
     */
    private Set<Position> tresPositions = new HashSet<Position>();

    /**
     * Whether the game is over.
     * <p>
     * This implements the element <b>over</b>.
     */
    public boolean isOver = false;

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

    /** Creates a new instance of the {@code Game} class. */
    public Game() {
    }

    /** Launches the game by creating a new thread and starting it. */
    public void launch() {
        this.gameThread = new Thread(this);

        this.gameThread.start();
    }

    /**
     * Gets an integer input, corresponding to a position's coordinates on the
     * board, from a player through
     * {@code stdin}.
     * 
     * @param scanner    The shell input text scanner.
     * @param isStealing Whether the player will steal or occupy a position.
     * @return The position at the inputted coordinates.
     */
    private Position getPositionInput(Scanner scanner, boolean isStealing) {
        Position position;

        while (true) {
            System.out.print("Input a position's coordinates (XY): ");

            int coordinatesInput;

            try {
                coordinatesInput = scanner.nextInt();
            } catch (InputMismatchException exception) {
                scanner.nextLine();

                coordinatesInput = 0;
            }

            if (!Board.POSITION_COORDINATES.contains(coordinatesInput)) {
                System.out.println("Please input an existing position's coordinates.");

                continue;
            }

            position = new Position(coordinatesInput / 10, coordinatesInput % 10);

            if (!isStealing && !this.remainingBoardPositions.contains(position)) {
                System.out.println("Please input an unoccupied position's coordinates.");

                continue;
            } else if (isStealing && this.remainingBoardPositions.contains(position)) {
                System.out.println("Please input an occupied position's coordinates.");

                continue;
            }

            break;
        }

        return position;
    }

    /**
     * Updates the position to be occupied by a player or returned to the board.
     * <p>
     * This implements the function <b>NextPlayerMove</b>(<i>pos</i> ∈ <b>P</b>).
     * 
     * @param position The position to update.
     */
    private void updatePosition(Position position) {
        if (this.isOccupyingTurn && this.isUnoTurn && this.remainingBoardPositions.contains(position)) {
            this.unoPositions.add(position);
            this.remainingBoardPositions.remove(position);

            this.isOccupyingTurn = !this.isOccupyingTurn;
            this.isUnoTurn = !this.isUnoTurn;
        } else if (!this.isOccupyingTurn
                && (this.unoPositions.contains(position) || this.tresPositions.contains(position))) {
            if (this.unoPositions.contains(position)) {
                this.unoPositions.remove(position);
            } else {
                this.tresPositions.remove(position);
            }

            this.remainingBoardPositions.add(position);

            this.isOccupyingTurn = !this.isOccupyingTurn;
        } else if (this.isOccupyingTurn && !this.isUnoTurn && this.remainingBoardPositions.contains(position)) {
            this.tresPositions.add(position);
            this.remainingBoardPositions.remove(position);

            this.isUnoTurn = !this.isUnoTurn;
        }
    }

    /**
     * Gets the ID name (Uno, Dos, or Tres) of the player that won the game.
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
     * Runs the "game loop" responsible for keeping new player turns coming until
     * the game is over. The winner will be
     * proclaimed once the game is over.
     */
    @Override
    public void run() {
        this.remainingBoardPositions = new HashSet<Position>(Board.POSITIONS);
        var scanner = new Scanner(System.in);

        while (true) {
            this.isOver = Game.WINNING_CONDITIONS.stream()
                    .anyMatch((condition) -> this.unoPositions.containsAll(condition))
                    || Game.WINNING_CONDITIONS.stream()
                            .anyMatch((condition) -> this.tresPositions.containsAll(condition))
                    || this.remainingBoardPositions.isEmpty();

            this.board.print(this.unoPositions, this.tresPositions);

            if (this.isOver) {
                break;
            }

            System.out.println(
                    (this.isOccupyingTurn && this.isUnoTurn
                            ? "Uno's"
                            : this.isOccupyingTurn && !this.isUnoTurn ? "Tres'" : "Dos'") + " Turn\n");

            var position = this.getPositionInput(scanner, !this.isOccupyingTurn);

            this.updatePosition(position);

            System.out.println();
        }

        System.out.println("Result: " + this.getWinner());

        scanner.close();
    }
}
