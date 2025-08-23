/*
 * JavaJeeps simulates managing and interacting with a coffee truck business.
 * Copyright (C) 2025 Raphael Panaligan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

package cielsachen.javajeeps.mco2.exception;

import cielsachen.javajeeps.mco2.model.Ingredient;

/** Represents an exception when a storage bin has insufficient capacity for an operation. */
public class InsufficientCapacityException extends Exception {
    /** The ingredient of the storage bin. */
    public final Ingredient ingredient;

    /**
     * Creates and returns a new {@code InsufficientCapacityException} object instance.
     *
     * @param ingredient The ingredient of the storage bin.
     */
    public InsufficientCapacityException(Ingredient ingredient) {
        super("The selected truck does not have enough " + ingredient + " to brew the coffee!");

        this.ingredient = ingredient;
    }
}
