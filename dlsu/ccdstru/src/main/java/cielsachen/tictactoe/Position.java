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

/** Represents a position on the board. */
public record Position(int columnNumber, int rowNumber) {
    /**
     * Flattens the column and row number values into a single integer.
     *
     * @return The flattened coordinates.
     */
    public int flatten() {
        return this.columnNumber * 10 + this.rowNumber;
    }
}
