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

import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingConstants;

/** Represents the window containing the main menu. */
public class MainMenuView extends JFrame {
    /** The button to click to create a new truck. */
    public final JButton createTruckButton = new JButton("Create a Coffee Truck");
    /** The button to click to simulate a truck's features. */
    public final JButton simulateButton = new JButton("Simulate");
    /** The button to click to view the dashboard. */
    public final JButton dashboardButton = new JButton("Dashboard");

    /** Creates and returns a new {@code MainMenuView} object instance. */
    public MainMenuView() {
        super("JavaJeeps: MCO2");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        getRootPane().setDefaultButton(createTruckButton);

        setLayout(new GridBagLayout());

        var subtitleLabel = new JLabel("What Would You Like to Do?");
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
        constraints.ipadx = constraints.ipady = 10;

        add(createTruckButton, constraints);

        constraints.gridy++;

        add(simulateButton, constraints);

        constraints.gridy++;
        constraints.insets.bottom = 20;

        add(dashboardButton, constraints);

        pack();
        setResizable(false);

        setLocationRelativeTo(null);
    }
}
