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

import java.util.InputMismatchException;
import java.util.Scanner;

/** The helper methods for getting specific input types through the CLI. */
public class Input {
    private final Scanner scanner;

    /**
     * Creates and returns a new {@code Input} object instance.
     *
     * @param scanner The scanner to use.
     */
    public Input(Scanner scanner) {
        this.scanner = scanner;
    }

    /**
     * Gets a boolean input from the user.
     *
     * @param prompt    The prompt to show the user.
     * @param isNewLine Whether the prompt is printed on a new line.
     * @return The user's boolean input.
     */
    public boolean getBoolean(String prompt, boolean isNewLine) {
        while (true) {
            try {
                if (isNewLine) {
                    System.out.println();
                }

                System.out.print(prompt + " ");

                boolean givenBool = scanner.nextBoolean();

                scanner.nextLine();

                return givenBool;
            } catch (InputMismatchException e) {
                scanner.nextLine();

                System.out.println();

                ExceptionMessage.INVALID_BOOLEAN_INPUT.print();

                if (!isNewLine) {
                    System.out.println();
                }
            }
        }
    }

    /**
     * Gets a boolean input from the user.
     *
     * @param prompt The prompt to show the user.
     * @return The user's boolean input.
     */
    public boolean getBoolean(String prompt) {
        return getBoolean(prompt, false);
    }

    /**
     * Gets a character input from the user.
     *
     * @param isNewLine Whether the prompt is printed on a new line.
     * @return The user's character input.
     */
    public char getCharacter(boolean isNewLine) {
        try {
            if (isNewLine) {
                System.out.println();
            }

            return Character.toUpperCase(scanner.nextLine().charAt(0));
        } catch (StringIndexOutOfBoundsException e) {
            return ' ';
        }
    }

    /**
     * Gets a character input from the user.
     *
     * @return The user's character input.
     */
    public char getCharacter() {
        return getCharacter(false);
    }

    /**
     * Gets a float input from the user.
     *
     * @param prompt    The prompt to show the user.
     * @param isNewLine Whether the prompt is printed on a new line.
     * @return The user's float input.
     */
    public float getFloat(String prompt, boolean isNewLine) {
        while (true) {
            try {
                if (isNewLine) {
                    System.out.println();
                }

                System.out.print(prompt + " ");

                float givenFloat = scanner.nextFloat();

                scanner.nextLine();

                return givenFloat;
            } catch (InputMismatchException e) {
                scanner.nextLine();

                System.out.println();

                ExceptionMessage.INVALID_FLOAT_INPUT.print();

                if (!isNewLine) {
                    System.out.println();
                }
            }
        }
    }

    /**
     * Gets a float input from the user.
     *
     * @param prompt The prompt to show the user.
     * @return The user's float input.
     */
    public float getFloat(String prompt) {
        return getFloat(prompt, false);
    }

    /**
     * Gets an integer input from the user.
     *
     * @param prompt    The prompt to show the user.
     * @param isNewLine Whether the prompt is printed on a new line.
     * @return The user's integer input.
     */
    public int getInteger(String prompt, boolean isNewLine) {
        while (true) {
            try {
                if (isNewLine) {
                    System.out.println();
                }

                System.out.print(prompt + " ");

                int givenInt = scanner.nextInt();

                scanner.nextLine();

                return givenInt;
            } catch (InputMismatchException e) {
                scanner.nextLine();

                System.out.println();

                ExceptionMessage.INVALID_INTEGER_INPUT.print();

                if (!isNewLine) {
                    System.out.println();
                }
            }
        }
    }

    /**
     * Gets an integer input from the user.
     *
     * @param prompt The prompt to show the user.
     * @return The user's integer input.
     */
    public int getInteger(String prompt) {
        return getInteger(prompt, false);
    }
}
