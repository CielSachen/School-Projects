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
import java.util.ArrayList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.text.PlainDocument;

import cielsachen.javajeeps.mco2.model.coffee.Coffee;
import cielsachen.javajeeps.mco2.validator.FloatDocumentFilter;

/** Represents the window containing a form for setting the prices of all coffees and add-ons. */
public class PriceConfigurationForm extends JFrame {
    /** The fields to input the prices of each coffee and add-on. */
    public final List<JTextField> priceFields = new ArrayList<>();
    /** The button to click to submit the selection. */
    public final JButton submitButton = new JButton("Submit");

    /**
     * Creates and returns a new {@code PriceConfigurationForm} object instance.
     *
     * @param parentComp The parent component of the window.
     * @param coffees    The coffees to use.
     */
    public PriceConfigurationForm(Component parentComp, Coffee[] coffees) {
        super("Coffee Prices Configuration");

        for (int i = 0; i < coffees.length + 2; i++) {
            var priceField = new JTextField();

            ((PlainDocument) priceField.getDocument()).setDocumentFilter(new FloatDocumentFilter());

            priceFields.add(priceField);
        }

        submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                if (priceFields.stream().anyMatch((pf) -> pf.getText().isEmpty())) {
                    return;
                }

                dispose();
            }
        });

        setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        getRootPane().setDefaultButton(submitButton);

        setLayout(new GridBagLayout());

        var constraints = new GridBagConstraints();
        constraints.gridx = 0;
        constraints.gridy = -1;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets = new Insets(20, 20, 20, 20);

        int i;

        for (i = 0; i < coffees.length; i++) {
            addLabeledComponent(new JLabel(coffees[i].name), priceFields.get(i), constraints);
        }

        constraints.gridx++;
        int maxGridY = constraints.gridy + 2;
        constraints.gridy = 0;

        addLabeledComponent(new JLabel("Extra Espresso Shot"), priceFields.get(i), constraints);
        addLabeledComponent(new JLabel("Add-on Syrup"), priceFields.get(i + 1), constraints);

        constraints.gridy = maxGridY + 1;
        constraints.insets.top = constraints.insets.left;
        constraints.insets.bottom = constraints.insets.left;

        add(submitButton, constraints);

        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }

    private void addLabeledComponent(JLabel labelComp, Component comp, GridBagConstraints constraints) {
        constraints.gridy++;
        constraints.insets.bottom = 2;

        add(labelComp, constraints);

        constraints.gridy++;
        constraints.insets.top = constraints.insets.bottom;
        constraints.insets.bottom = 4;

        add(comp, constraints);
    }
}
