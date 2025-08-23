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

package cielsachen.javajeeps.mco1.model.coffee;

import java.util.stream.Stream;

import cielsachen.javajeeps.mco1.model.Ingredient;

/** Represents the ratio of coffee beans to water in a shot of espresso. */
public enum EspressoRatio {
    /** The customizable ratio (of water only) of coffee beans to water. */
    CUSTOM("Custom", 1, 0),
    /** The standard light ratio of coffee beans to water. */
    LIGHT("Light", 1, 20),
    /** The standard ratio of coffee beans to water. */
    STANDARD("Standard", 1, 18),
    /** The standard strong ratio of coffee beans to water. */
    STRONG("Strong", 1, 15);

    /** The name of the espresso ratio. */
    public final String name;

    /** The ratio of coffee beans. */
    public final double coffeeBean;
    /** The decimal ratio of coffee beans. */
    public final double coffeeBeanDecimal;

    private double water;

    private EspressoRatio(String name, double coffeeBeanRatio, double waterRatio) {
        this.name = name;

        coffeeBean = coffeeBeanRatio;
        coffeeBeanDecimal = coffeeBeanRatio / (waterRatio + 1);

        water = waterRatio;
    }

    /**
     * Gets the standard espresso ratios.
     *
     * @return The standard espresso ratios.
     */
    public static EspressoRatio[] regularValues() {
        return Stream.of(EspressoRatio.values()).filter((er) -> !er.equals(CUSTOM)).toArray(EspressoRatio[]::new);
    }

    /**
     * Sets the ratio of the {@link EspressoRatio#CUSTOM custom espresso ratio}.
     *
     * @param waterRatio The water ratio to use.
     */
    public static void setCustomRatio(double waterRatio) {
        CUSTOM.setWater(waterRatio);
    }

    /**
     * Gets the ratio of water.
     *
     * @return The ratio of water.
     */
    public double getWater() {
        return water;
    }

    /**
     * Sets the ratio of water.
     *
     * @param newWaterRatio The ratio of water to use.
     */
    private void setWater(double newWaterRatio) {
        water = newWaterRatio;
    }

    /**
     * Gets the decimal ratio of water.
     *
     * @return The decimal ratio of water.
     */
    public double getWaterDecimal() {
        return water / (water + 1);
    }

    /**
     * Converts the espresso ratio into its string representation.
     *
     * @return The stylized coffee beans to water ratio.
     */
    @Override
    public String toString() {
        if (this.equals(CUSTOM) && CUSTOM.water == 0) {
            return "Customize";
        }

        return name + " (" + (int) coffeeBean + " " + Ingredient.COFFEE_BEANS + " : " + (int) water + " "
                + Ingredient.WATER + ")";
    }
}
