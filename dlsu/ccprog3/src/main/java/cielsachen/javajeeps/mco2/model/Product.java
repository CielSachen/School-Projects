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

/** Represents a purchasable product. */
public class Product {
    /** The default initial price of a product. */
    public static final float DEFAULT_PRICE = -1;

    /** The price of the product. */
    protected float price = DEFAULT_PRICE;

    /** Creates and returns a new {@code Product} object instance. */
    public Product() {
    }

    /**
     * Gets the price of the product.
     *
     * @return The price of the product.
     */
    public float getPrice() {
        return price;
    }

    /**
     * Sets the price of the product.
     *
     * @param newPrice The new price to use.
     * @return Whether the price of the product was changed.
     */
    public boolean setPrice(float newPrice) {
        if (newPrice < 0) {
            return false;
        }

        price = newPrice;

        return true;
    }

    /**
     * Converts the product into its price string representation.
     *
     * @return The stylized price of the product.
     */
    public String toPriceString() {
        return price + " PHP";
    }
}
