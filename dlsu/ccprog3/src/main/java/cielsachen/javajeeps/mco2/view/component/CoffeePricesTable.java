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

import java.util.stream.Stream;

import javax.swing.JTable;

import cielsachen.javajeeps.mco2.model.coffee.Coffee;
import cielsachen.javajeeps.mco2.model.coffee.CoffeeSize;

/** Represents a table containing a coffee's prices per size. */
public class CoffeePricesTable extends JTable {
    /**
     * Creates and returns a new {@code CoffeePricesTable} object instance.
     *
     * @param coffees The coffees to use.
     */
    public CoffeePricesTable(Coffee[] coffees) {
        super(Stream
                .of(coffees)
                .map((c) -> new String[] {
                        c.name,
                        c.toPriceString(CoffeeSize.SMALL_CUP),
                        c.toPriceString(CoffeeSize.MEDIUM_CUP),
                        c.toPriceString(CoffeeSize.LARGE_CUP)
                })
                .toArray(String[][]::new), new String[] { "Coffee", "Price (S)", "Price (M)", "Price (L)" });
    }
}
