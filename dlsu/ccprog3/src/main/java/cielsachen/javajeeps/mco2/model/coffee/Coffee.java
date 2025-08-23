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
import cielsachen.javajeeps.mco2.model.Product;

/** Represents a brewable coffee. */
public class Coffee extends Product {
    private static final float PRICE_SIZE_MODIFIER = 0.1f;

    /** The name of the coffee. */
    public final String name;
    /** The extra ingredient needed to brew the coffee. */
    public final Ingredient extraIngredient;

    /** The ratio of espresso to use to brew the coffee. */
    public final double espressoRatio;
    /** The ratio of the extra ingredient to use to brew the coffee. */
    public final double extraIngredientRatio;

    /**
     * Creates and returns a new {@code Coffee} object instance.
     *
     * @param name                 The name of the coffee.
     * @param extraIngredient      The extra ingredient needed to brew the coffee.
     * @param espressoRatio        The ratio of espresso to use to brew the coffee.
     * @param extraIngredientRatio The ratio of the extra ingredient to use to brew the coffee.
     */
    public Coffee(String name, Ingredient extraIngredient, double espressoRatio, double extraIngredientRatio) {
        this.name = name;
        this.extraIngredient = extraIngredient;

        this.espressoRatio = espressoRatio;
        this.extraIngredientRatio = extraIngredientRatio;
    }

    /**
     * Gets the price of the coffee based on a size.
     *
     * @param size The size of the coffee.
     * @return The price of the coffee based on the size.
     */
    public float getPrice(CoffeeSize size) {
        return switch (size) {
            case CoffeeSize.SMALL_CUP -> price - price * PRICE_SIZE_MODIFIER;
            case CoffeeSize.LARGE_CUP -> price + price * PRICE_SIZE_MODIFIER;
            default -> price;
        };
    }

    /**
     * Converts the coffee into its string representation.
     *
     * @return The name of the coffee.
     */
    @Override
    public String toString() {
        return name;
    }

    /**
     * Converts the coffee into its price string representation.
     *
     * @return The stylized prices of all sizes of the coffee.
     */
    @Override
    public String toPriceString() {
        return "(S) " + getPrice(CoffeeSize.SMALL_CUP) + " PHP / (M) " + price + " PHP / (L) "
                + getPrice(CoffeeSize.LARGE_CUP) + " PHP";
    }

    /**
     * Converts the coffee into its price string representation.
     *
     * @param size The size of the coffee.
     * @return The stylized price of a medium cup of the coffee.
     */
    public String toPriceString(CoffeeSize size) {
        return getPrice(size) + " PHP";
    }
}
