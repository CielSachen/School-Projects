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

package cielsachen.javajeeps.mco1.helper;

/** Represents a ANSI escape code for printing text in a different color. */
public enum PrintColor {
    /** The ANSI escape code for printing text in bright cyan. */
    BRIGHT_CYAN("0;96"),
    /** The ANSI escape code for printing text in bright green. */
    BRIGHT_GREEN("0;92"),
    /** The ANSI escape code for printing text in bright yellow. */
    BRIGHT_YELLOW("0;93"),
    /** The ANSI escape code for printing text in red. */
    RED("0;31"),
    /** The ANSI escape code for printing text in the default color. */
    RESET("0"),
    /** The ANSI escape code for printing text in yellow. */
    YELLOW("0;33");

    /** The ANSI escape code of the color. */
    public final String escapeCode;

    private PrintColor(String code) {
        escapeCode = "\033[" + code + "m";
    }

    /**
     * Sets the print color of a piece of text.
     *
     * @param text  The text to colorize.
     * @param color The color to set to.
     * @return The colorized piece of text.
     */
    public static String set(String text, PrintColor color) {
        return color + text + RESET;
    }

    /**
     * Converts the ANSI escape code into its string representation.
     *
     * @return The ANSI escape code of the color.
     */
    @Override
    public String toString() {
        return escapeCode;
    }
}
