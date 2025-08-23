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

/** Represents a message describing or giving a remedy for an exception. */
public enum ExceptionMessage {
    /** The message giving a remedy for an invalid boolean input. */
    INVALID_BOOLEAN_INPUT("Please only input `true` or `false`!"),
    /** The message giving a remedy for choosing an invalid character. */
    INVALID_CHARACTER_CHOICE("Please only chose from the given character choices!"),
    /** The message giving a remedy for an invalid float input. */
    INVALID_FLOAT_INPUT("Please only input a floating point number!"),
    /** The message giving a remedy for choosing an invalid integer. */
    INVALID_INTEGER_CHOICE("Please only chose from the given integer choices!"),
    /** The message giving a remedy for an invalid integer input. */
    INVALID_INTEGER_INPUT("Please only input a whole number!");

    /** The message for the exception. */
    public final String message;

    private ExceptionMessage(String msg) {
        message = msg;
    }

    /**
     * Prints a custom message with proper formatting.
     *
     * @param message The message to print.
     */
    public static void printCustom(String message) {
        System.out.println(PrintColor.set(message, PrintColor.RED));
    }

    /** Prints the exception's message with proper formatting. */
    public void print() {
        System.out.println(PrintColor.set(message, PrintColor.RED));
    }

    /**
     * Converts the exception message into its string representation.
     *
     * @return The message for the exception.
     */
    @Override
    public String toString() {
        return message;
    }
}
