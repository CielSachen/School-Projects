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

import java.util.Collections;
import java.util.List;
import java.util.Map;

import cielsachen.javajeeps.mco2.model.coffee.CoffeeSize;

/** Represents the purchase of a coffee from a truck. */
public class Transaction {
    /** The name of the purchased coffee. */
    public final String coffeeName;
    /** The size of the purchased coffee. */
    public final CoffeeSize coffeeSize;
    /** The number of extra espresso shots added. */
    public final int extraEspressoShotCount;
    /** The total cost of purchasing the coffee. */
    public final float cost;

    /** The truck the coffee was purchased from. */
    public final Truck truck;

    private final Map<Ingredient, Double> ingredientToAmount;

    /**
     * Creates and returns a new {@code Transaction} object instance.
     *
     * @param coffeeName           The name of the purchased coffee.
     * @param coffeeSize           The size of the purchased coffee.
     * @param cost                 The total cost of purchasing the coffee.
     * @param truck                The truck the coffee was purchased from.
     * @param extraEspressoShotCnt The number of extra espresso shots added.
     * @param ingredientToAmount   The ingredients used to brew the coffee mapped to their amounts.
     */
    public Transaction(String coffeeName, CoffeeSize coffeeSize, float cost, Truck truck, int extraEspressoShotCnt,
            Map<Ingredient, Double> ingredientToAmount) {
        this.coffeeName = coffeeName;
        this.coffeeSize = coffeeSize;
        extraEspressoShotCount = extraEspressoShotCnt;
        this.cost = cost;

        this.truck = truck;

        this.ingredientToAmount = ingredientToAmount;
    }

    /**
     * Gets the ingredients used to brew the coffee.
     *
     * @return The immutable mapping of ingredients used to their amounts.
     */
    public Map<Ingredient, Double> getIngredients() {
        return Collections.unmodifiableMap(ingredientToAmount);
    }

    /**
     * Gets the syrups added to the coffee.
     *
     * @return The immutable list of syrups added to the coffee.
     */
    public List<Ingredient> getSyrups() {
        return ingredientToAmount
                .entrySet()
                .stream()
                .filter((e) -> e.getKey().isSpecial)
                .map((e) -> e.getKey())
                .toList();
    }

    /**
     * Converts the transaction into its cost string representation.
     *
     * @return The stylized total cost of purchasing the coffee.
     */
    public String toCostString() {
        return cost + " PHP";
    }
}
