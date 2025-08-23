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

package cielsachen.javajeeps.mco1.model;

import java.util.stream.Stream;

/** Represents an ingredient for brewing coffee. */
public enum Ingredient {
    /** A small cup to store coffee for drinking. */
    SMALL_CUP("Small Cups", 80, "pcs"),
    /** A medium cup to store coffee for drinking. */
    MEDIUM_CUP("Medium Cups", 64, "pcs"),
    /** A large cup to store coffee for drinking. */
    LARGE_CUP("Large Cups", 40, "pcs"),
    /** Coffee beans used for brewing coffee. */
    COFFEE_BEANS("Coffee Beans", 1008, "g"),
    /** Milk used for brewing coffee. */
    MILK("Milk", 640, "fl oz"),
    /** Water used for brewing coffee. */
    WATER("Water", 640, "fl oz"),

    /** Hazelnut syrup that can be added to a coffee. */
    HAZELNUT_SYRUP("Hazelnut Syrup", true, 640, "fl oz"),
    /** Chocolate syrup that can be added to a coffee. */
    CHOCOLATE_SYRUP("Chocolate Syrup", true, 640, "fl oz"),
    /** Almond syrup that can be added to a coffee. */
    ALMOND_SYRUP("Almond Syrup", true, 640, "fl oz"),
    /** Sweetener that can be added to a coffee. */
    SWEETENER("Sweetener (Sucrose)", true, 640, "fl oz");

    /** The name of the ingredient. */
    public final String name;
    /** Whether the ingredient is for special trucks. */
    public final boolean isSpecial;
    /** The maximum storage bin capacity of the ingredient. */
    public final double maxCapacity;
    /** The unit of measure for a quantity of the ingredient. */
    public final String unitMeasure;

    private Ingredient(String name, boolean isSpecial, double maxCapacity, String unitMeasure) {
        this.name = name;
        this.isSpecial = isSpecial;
        this.maxCapacity = maxCapacity;
        this.unitMeasure = unitMeasure;
    }

    private Ingredient(String name, double maxCapacity, String unitMeasure) {
        this(name, false, maxCapacity, unitMeasure);
    }

    /**
     * Gets the ingredients that can be used by any truck.
     *
     * @return The non-special ingredients.
     */
    public static Ingredient[] regularValues() {
        return Stream.of(Ingredient.values()).filter((i) -> !i.isSpecial).toArray(Ingredient[]::new);
    }

    /**
     * Gets the ingredients that can only be used by special trucks.
     *
     * @return The special ingredients.
     */
    public static Ingredient[] specialValues() {
        return Stream.of(Ingredient.values()).filter((i) -> i.isSpecial).toArray(Ingredient[]::new);
    }

    /**
     * Converts the ingredient into its string representation.
     *
     * @return The name of the ingredient.
     */
    @Override
    public String toString() {
        return name;
    }
}
