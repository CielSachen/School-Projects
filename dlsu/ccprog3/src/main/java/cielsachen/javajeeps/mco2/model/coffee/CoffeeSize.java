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

package cielsachen.javajeeps.mco2.model.coffee;

import cielsachen.javajeeps.mco2.model.Ingredient;

/** Represents the size of a coffee. */
public enum CoffeeSize {
    /** A small cup of coffee. */
    SMALL_CUP(8, Ingredient.SMALL_CUP),
    /** A medium cup of coffee. */
    MEDIUM_CUP(12, Ingredient.MEDIUM_CUP),
    /** A large cup of coffee. */
    LARGE_CUP(16, Ingredient.LARGE_CUP);

    /** The cup of the size. */
    public final Ingredient cup;
    /** The capacity of a cup of the size. */
    public final int capacity;
    /** The unit of measure for the capacity of the cup. */
    public final String unitMeasure = "fl oz";

    private CoffeeSize(int capacity, Ingredient cup) {
        this.cup = cup;
        this.capacity = capacity;
    }

    /**
     * Converts the size into its string representation.
     *
     * @return The stylized capacity of a cup of the size.
     */
    @Override
    public String toString() {
        return cup.name.substring(0, cup.name.length() - 1) + " (" + capacity + " " + unitMeasure + ")";
    }
}
