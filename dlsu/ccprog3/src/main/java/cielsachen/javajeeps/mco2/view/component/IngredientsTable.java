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

package cielsachen.javajeeps.mco2.view.component;

import java.util.Map;

import javax.swing.JTable;

import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.Transaction;

/** Represents a table containing information about ingredients. */
public class IngredientsTable extends JTable {
    /**
     * Creates and returns a new {@code IngredientsTable} object instance.
     *
     * @param ingredientToAmount The ingredients mapped to their amounts.
     */
    public IngredientsTable(Map<Ingredient, Double> ingredientToAmount) {
        super(ingredientToAmount
                .entrySet()
                .stream()
                .map((entry) -> {
                    Ingredient ingredient = entry.getKey();

                    return new String[] {
                            ingredient.name,
                            String.format("%.2f %s", entry.getValue(), ingredient.unitMeasure),
                    };
                })
                .toArray(String[][]::new), new String[] { "Ingredient", "Amount" });
    }

    /**
     * Creates and returns a new {@code IngredientsTable} object instance.
     *
     * @param transaction The transaction to use.
     */
    public IngredientsTable(Transaction transaction) {
        this(transaction.getIngredients());
    }
}
