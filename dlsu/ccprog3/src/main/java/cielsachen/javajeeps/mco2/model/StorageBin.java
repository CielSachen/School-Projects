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

package cielsachen.javajeeps.mco2.model;

/** Represents a bin storing an ingredient on a truck. */
public class StorageBin {
    /** The number of storage bins a standard truck has. */
    public static final int STANDARD_TRUCK_COUNT = 8;
    /** The number of storage bins a special truck has. */
    public static final int SPECIAL_TRUCK_COUNT = 10;

    /** The one-based ID of the storage bin. */
    public final int id;
    /** The truck the storage bin belongs to. */
    public final Truck truck;

    private Ingredient ingredient;
    private double capacity = 0;

    /**
     * Creates and returns a new {@code StorageBin} object instance.
     *
     * @param id         The ID of the storage bin.
     * @param truck      The truck the storage bin belongs to.
     * @param ingredient The ingredient the storage bin contains.
     */
    public StorageBin(int id, Truck truck, Ingredient ingredient) {
        this.id = id;
        this.truck = truck;

        this.ingredient = ingredient;
        capacity = ingredient.maxCapacity;
    }

    /**
     * Gets ingredient the storage bin contains.
     *
     * @return The ingredient the storage bin contains.
     */
    public Ingredient getIngredient() {
        return ingredient;
    }

    /**
     * Sets ingredient the storage bin will contain.
     *
     * @param newIngredient The new ingredient to contain.
     */
    public void setIngredient(Ingredient newIngredient) {
        ingredient = newIngredient;
    }

    /**
     * Gets the capacity of the storage bin.
     *
     * @return The capacity of the storage bin.
     */
    public double getCapacity() {
        return capacity;
    }

    /**
     * Decreases the capacity of the storage bin.
     *
     * @param deductibleCapacity The amount to decrease by. If the amount is greater than the current capacity, the
     *                           capacity will not be decreased.
     * @return Whether the capacity of the storage bin was decreased.
     */
    public boolean decreaseCapacity(double deductibleCapacity) {
        if (deductibleCapacity > capacity) {
            return false;
        }

        capacity -= deductibleCapacity;

        return true;
    }

    /**
     * Increases the capacity of the storage bin.
     *
     * @param additionalCapacity The amount to increase by. If the amount is zero or negative, capacity will not be
     *                           increased.
     * @return Whether the capacity of the storage bin was increased.
     */
    public boolean increaseCapacity(double additionalCapacity) {
        if (additionalCapacity <= 0) {
            return false;
        }

        capacity += additionalCapacity;

        return true;
    }

    /**
     * Checks whether the capacity of the storage bin is at a critical-level.
     *
     * @return Whether the capacity of the storage bin is less than a third of the maximum.
     */
    public boolean isCriticalCapacity() {
        return capacity < ingredient.maxCapacity / 3;
    }

    /**
     * Converts the storage bin into its string representation.
     *
     * @return The ID of the storage bin.
     */
    @Override
    public String toString() {
        return String.format("Storage Bin %d (Contains %s)", id, ingredient);
    }

    /**
     * Converts the storage bin into its capacity string representation.
     *
     * @return The stylized capacity of the storage bin.
     */
    public String toCapacityString() {
        return String.format("%.2f / %.2f %s", capacity, ingredient.maxCapacity, ingredient.unitMeasure);
    }
}
