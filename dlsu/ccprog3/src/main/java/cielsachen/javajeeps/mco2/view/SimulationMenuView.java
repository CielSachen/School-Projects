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

/** Represents the window containing the simulation menu. */
public class SimulationMenuView extends JFrame {
    /** The button to click to simulate the sale of coffee. */
    public final JButton coffeeSaleButton = new JButton("Sale and Preparation of the Coffee Drink");
    /** The button to click to view information about a truck. */
    public final JButton viewTruckButton = new JButton("View Truck Information");
    /** The button to click to restock a truck's storage bins. */
    public final JButton restockButton = new JButton("Restocking of Storage Bins");
    /** The button to click to perform maintenance on a truck. */
    public final JButton maintenanceButton = new JButton("Maintenance");

    /**
     * Creates and returns a new {@code SimulationForm} object instance.
     *
     * @param parentComp The parent component of the window.
     */
    public SimulationMenuView(Component parentComp) {
        super("Feature Simulator");

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        getRootPane().setDefaultButton(coffeeSaleButton);

        setLayout(new GridBagLayout());

        var subtitleLabel = new JLabel("Which feature would you like to simulate?");
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

        add(coffeeSaleButton, constraints);

        constraints.gridy++;

        add(viewTruckButton, constraints);

        constraints.gridy++;

        add(restockButton, constraints);

        constraints.gridy++;
        constraints.insets.bottom = 20;

        add(maintenanceButton, constraints);

        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }
}
