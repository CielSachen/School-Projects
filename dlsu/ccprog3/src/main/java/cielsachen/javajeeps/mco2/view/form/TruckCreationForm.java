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
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

/** Represents the window containing the form for inputting the properties of a new truck. */
public class TruckCreationForm extends JFrame {
    /** The field to input the desired location of the truck. */
    public final JTextField locationField = new JTextField();
    /** The checkbox to mark to signify whether the truck should be special. */
    public final JCheckBox isSpecialCheckBox = new JCheckBox("Make a Special Truck?");
    /** The button to click to submit the selection. */
    public final JButton submitButton = new JButton("Submit");

    /**
     * Creates and returns a new {@code TruckCreationForm} object instance.
     *
     * @param parentComp The parent component of the window.
     */
    public TruckCreationForm(Component parentComp) {
        super("Truck Creation");

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                if (locationField.getText().isEmpty()) {
                    return;
                }

                dispose();
            }
        });

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        getRootPane().setDefaultButton(submitButton);

        setLayout(new GridBagLayout());

        var constraints = new GridBagConstraints();
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets = new Insets(20, 20, 2, 20);

        add(new JLabel("Where will this truck be located?"), constraints);

        constraints.gridy++;
        constraints.insets.top = constraints.insets.bottom;

        add(locationField, constraints);

        constraints.gridy++;

        add(isSpecialCheckBox, constraints);

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
