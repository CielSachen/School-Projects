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
import java.util.List;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.StorageBin;
import cielsachen.javajeeps.mco2.view.component.TableSize;

/** Represents the window containing a form for selecting the new ingredient a storage bin should contain. */
public class IngredientSelectionForm extends JFrame {
    /** The selection of ingredients to select from. */
    public final JComboBox<Ingredient> ingredientComboBox;
    /** The button to click to submit the selection. */
    public final JButton submitButton = new JButton("Submit");

    /**
     * Creates and returns a new {@code IngredientSelectionForm} object instance.
     *
     * @param parentComp  The parent component of the window.
     * @param storageBins The storage bins to use for context. This should exclude the storage bin whose ingredient
     *                    is being replaced.
     * @param ingredients The list of ingredients to use.
     */
    public IngredientSelectionForm(Component parentComp, List<StorageBin> storageBins, List<Ingredient> ingredients) {
        super("Storage Bin Selection");

        ingredientComboBox = new JComboBox<>(ingredients.toArray(Ingredient[]::new));

        submitButton.addActionListener((e) -> dispose());

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        getRootPane().setDefaultButton(submitButton);

        setLayout(new GridBagLayout());

        var constraints = new GridBagConstraints();
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.insets = new Insets(20, 20, 2, 20);

        add(new JLabel("What item should this storage bin contain instead?"), constraints);

        var storageBinsTablePane = new JScrollPane(new JTable(storageBins
                .stream()
                .map((sb) -> new String[] { Integer.toString(sb.id), sb.getIngredient().name })
                .toArray(String[][]::new), new String[] { "Storage Bin ID", "Ingredient" }));
        storageBinsTablePane.setPreferredSize(TableSize.SMALL.dimension);

        constraints.gridy++;
        constraints.weightx = 1;
        constraints.weighty = 1;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.insets.top = constraints.insets.bottom;

        add(storageBinsTablePane, constraints);

        constraints.gridy++;
        constraints.weighty = 0.5;
        constraints.insets.top = constraints.insets.bottom;

        add(ingredientComboBox, constraints);

        constraints.gridy++;
        constraints.weightx = 0;
        constraints.weighty = 0;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets.top = constraints.insets.bottom;
        constraints.insets.bottom = constraints.insets.left;

        add(submitButton, constraints);

        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }
}
