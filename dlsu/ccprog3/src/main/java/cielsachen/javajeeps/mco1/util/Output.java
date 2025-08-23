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

package cielsachen.javajeeps.mco1.util;

import cielsachen.javajeeps.mco1.helper.PrintColor;

/** The utility methods for printing formatted text CLI elements. */
public final class Output {
    private Output() {
    }

    /**
     * Prints a header with the proper formatting.
     *
     * @param header The header to print.
     */
    public static void printHeader1(String header) {
        System.out.println("---------- +  " + PrintColor.set(header, PrintColor.BRIGHT_YELLOW) + " + ----------");
    }

    /**
     * Prints a header with the proper formatting.
     *
     * @param header The header to print.
     */
    public static void printHeader2(String header) {
        System.out.println("----- + ----- +  " + PrintColor.set(header, PrintColor.BRIGHT_YELLOW) + " + ----- + -----");
    }

    /**
     * Prints a header with the proper formatting.
     *
     * @param header The header to print.
     */
    public static void printHeader3(String header) {
        System.out.println("----- +  " + PrintColor.set(header, PrintColor.BRIGHT_YELLOW) + " + -----");
    }

    /**
     * Prints a title with the proper formatting.
     *
     * @param title The title to print.
     */
    public static void printTitle(String title) {
        System.out.println("---------- + ---------- + " + PrintColor.set(title, PrintColor.BRIGHT_YELLOW)
                + " + ---------- + ----------");
    }
}
