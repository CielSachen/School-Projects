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

package cielsachen.javajeeps.mco2.view;

import java.awt.Component;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

/** Represents the window containing the storage bin restocking menu. */
public class StorageBinRestockingMenuView extends JFrame {
    /** The button to click to restock a storage bin. */
    public final JButton restockButton = new JButton("Restock");
    /** The button to click to empty a storage bin. */
    public final JButton emptyButton = new JButton("Empty");
    /** The button to click to change the ingredient a storage bin contains. */
    public final JButton changeIngredientButton = new JButton("Change Ingredients");

    /**
     * Creates and returns a new {@code StorageBinRestockingForm} object instance.
     *
     * @param parentComp The parent component of the window.
     */
    public StorageBinRestockingMenuView(Component parentComp) {
        super("Storage Bin Restocking");

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        getRootPane().setDefaultButton(restockButton);

        setLayout(new GridBagLayout());

        var subtitleLabel = new JLabel("What would you like to do to the storage bin?");
        subtitleLabel.setHorizontalAlignment(SwingConstants.CENTER);
        subtitleLabel.setFont(new Font("Arial", Font.BOLD, 25));

        var constraints = new GridBagConstraints();
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.insets = new Insets(20, 20, 20, 20);

        add(subtitleLabel, constraints);

        constraints.gridy++;
        constraints.insets.top = 5;
        constraints.insets.bottom = 5;
        constraints.ipadx = 10;
        constraints.ipady = 10;

        add(restockButton, constraints);

        constraints.gridy++;

        add(emptyButton, constraints);

        constraints.gridy++;
        constraints.insets.bottom = 20;

        add(changeIngredientButton, constraints);

        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }
}
