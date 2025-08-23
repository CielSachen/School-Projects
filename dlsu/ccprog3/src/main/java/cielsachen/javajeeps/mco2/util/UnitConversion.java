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

package cielsachen.javajeeps.mco2.util;

/** The utility methods for converting from one unit of measure to another. */
public final class UnitConversion {
    /** The number of grams in a fluid ounce. */
    public static final double FLUID_ONCES_TO_GRAMS = 28.34952;

    private UnitConversion() {
    }

    /**
     * Converts fluid ounces (fl oz) into the equivalent grams (g).
     *
     * @param fluidOunces The fluid ounces (fl oz) to convert.
     * @return The converted number of grams (g).
     */
    public static double fluidOuncesToGrams(double fluidOunces) {
        return fluidOunces * FLUID_ONCES_TO_GRAMS;
    }

    /**
     * Converts grams (g) into the equivalent fluid ounces (fl oz).
     *
     * @param grams The grams (g) to convert.
     * @return The converted number of fluid ounces (fl oz).
     */
    public static double gramsToFluidOunces(double grams) {
        return grams / FLUID_ONCES_TO_GRAMS;
    }
}
