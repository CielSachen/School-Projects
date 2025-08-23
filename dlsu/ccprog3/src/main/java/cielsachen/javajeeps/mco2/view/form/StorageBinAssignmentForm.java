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

package cielsachen.javajeeps.mco2.view.form;

import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;

import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.StorageBin;
import cielsachen.javajeeps.mco2.model.Truck;

/** Represents the window containing the form for setting the initial ingredients of all of a truck's storage bins. */
public class StorageBinAssignmentForm extends JFrame {
    /** The selections, for each storage bin, of ingredients to select from. */
    public final List<JComboBox<Ingredient>> ingredientComboBoxes = new ArrayList<>();
    /** The button to click to submit the selection. */
    public final JButton submitButton = new JButton("Submit");

    /**
     * Creates and returns a new {@code StorageBinAssignmentForm} object instance.
     *
     * @param parentComp The parent component of the window.
     * @param truck      The truck to use.
     */
    public StorageBinAssignmentForm(Component parentComp, Truck truck) {
        super("Storage Bin Assignment");

        for (int i = 0; i < (truck.isSpecial ? StorageBin.SPECIAL_TRUCK_COUNT : StorageBin.STANDARD_TRUCK_COUNT); i++) {
            ingredientComboBoxes.add(new JComboBox<>(i < StorageBin.STANDARD_TRUCK_COUNT
                    ? Ingredient.regularValues()
                    : Ingredient.specialValues()));
        }

        submitButton.addActionListener((e) -> dispose());

        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        getRootPane().setDefaultButton(submitButton);

        setLayout(new GridBagLayout());

        var constraints = new GridBagConstraints();
        constraints.gridx = 0;
        constraints.gridy = -1;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets = new Insets(20, 20, 20, 20);

        for (int i = 0; i < ingredientComboBoxes.size(); i++) {
            constraints.gridy++;
            constraints.insets.bottom = 2;

            add(new JLabel("Storage  Bin #" + i), constraints);

            constraints.gridy++;
            constraints.insets.top = constraints.insets.bottom;
            constraints.insets.bottom = 4;

            add(ingredientComboBoxes.get(i), constraints);
        }

        constraints.gridy++;
        constraints.insets.top = constraints.insets.left;
        constraints.insets.bottom = constraints.insets.left;

        add(submitButton, constraints);

        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }
}
