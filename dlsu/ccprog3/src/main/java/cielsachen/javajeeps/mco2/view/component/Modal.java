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

import java.awt.Component;
import java.util.List;

import javax.swing.JOptionPane;

/** Represents a smaller pop-up window. */
public final class Modal extends JOptionPane {
    private Modal() {
    }

    /**
     * Shows a confirmation dialog modal with yes or no buttons.
     *
     * @param parentComp The parent component of the modal.
     * @param msg        The message displayed in the modal.
     * @param title      The title of the modal.
     * @return Whether the user clicked yes or no.
     */
    public static int showConfirmDialog(Component parentComp, String msg, String title) {
        return JOptionPane.showConfirmDialog(parentComp, msg, title, YES_NO_OPTION);
    }

    /**
     * Shows a dialog modal containing an error message.
     *
     * @param parentComp The parent component of the modal.
     * @param msg        The error message displayed in the modal.
     * @param title      The title of the modal.
     */
    public static void showErrorDialog(Component parentComp, String msg, String title) {
        showMessageDialog(parentComp, msg, title, ERROR_MESSAGE);
    }

    /**
     * Shows a dialog modal that allows the user to input text in a field.
     *
     * @param parentComp The parent component of the modal.
     * @param msg        The message displayed in the modal.
     * @param title      The title of the modal.
     * @return The user's submitted text input.
     */
    public static String showInputDialog(Component parentComp, String msg, String title) {
        return JOptionPane.showInputDialog(parentComp, msg, title, PLAIN_MESSAGE);
    }

    /**
     * Shows a dialog modal that allows the user to select from a selection.
     *
     * @param <T>           The object type of the choices.
     * @param parentComp    The parent component of the modal.
     * @param msg           The message displayed in the modal.
     * @param title         The title of the modal.
     * @param choices       The choices to select from.
     * @param defaultChoice The default selected choice.
     * @return The user's submitted selected choice.
     */
    @SuppressWarnings("unchecked")
    public static <T extends Object> T showSelectionDialog(Component parentComp, String msg, String title, T[] choices,
            T defaultChoice) {
        return (T) JOptionPane.showInputDialog(parentComp, msg, title, PLAIN_MESSAGE, null, choices, defaultChoice);
    }

    /**
     * Shows a dialog modal that allows the user to select from a selection.
     *
     * @param <T>           The object type of the choices.
     * @param parentComp    The parent component of the modal.
     * @param msg           The message displayed in the modal.
     * @param title         The title of the modal.
     * @param choices       The list of choices to select from.
     * @param defaultChoice The default selected choice.
     * @return The user's submitted selected choice.
     */
    @SuppressWarnings("unchecked")
    public static <T extends Object> T showSelectionDialog(Component parentComp, String msg, String title,
            List<T> choices, T defaultChoice) {
        return (T) JOptionPane.showInputDialog(parentComp, msg, title, PLAIN_MESSAGE, null, choices.toArray(),
                defaultChoice);
    }
}
