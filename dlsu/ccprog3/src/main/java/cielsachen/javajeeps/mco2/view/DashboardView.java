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
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.List;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTable;
import javax.swing.SwingConstants;

import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.Transaction;
import cielsachen.javajeeps.mco2.view.component.IngredientsTable;
import cielsachen.javajeeps.mco2.view.component.TableSize;

/** Represents the window containing the dashboard. */
public class DashboardView extends JFrame {
    /**
     * Creates and returns a new {@code DashboardView} object instance.
     *
     * @param parentComp             The parent component of the window.
     * @param truckCnt               The number of trucks.
     * @param specialTruckCnt        The number of special trucks.
     * @param capacitiesByIngredient The ingredients mapped to their amounts.
     * @param transactions           The list of transactions linked with any truck.
     */
    public DashboardView(Component parentComp, int truckCnt, int specialTruckCnt,
            Map<Ingredient, Double> capacitiesByIngredient, List<Transaction> transactions) {
        super("Dashboard");

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        var panel = new JPanel(new GridBagLayout());

        var constraints = new GridBagConstraints();
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets = new Insets(20, 20, 2, 20);

        panel.add(new JLabel("Deployed Trucks: " + truckCnt), constraints);

        constraints.gridy++;
        constraints.insets.top = constraints.insets.bottom;

        panel.add(new JLabel("Special Trucks: " + specialTruckCnt), constraints);

        constraints.gridy++;
        constraints.fill = GridBagConstraints.NONE;
        constraints.insets.top = 4;

        panel.add(new JLabel("Ingredients"), constraints);

        var ingredientsTablePane = new JScrollPane(new JTable(
                capacitiesByIngredient
                        .entrySet()
                        .stream()
                        .map((entry) -> {
                            Ingredient ingredient = entry.getKey();

                            return new String[] {
                                    ingredient.name,
                                    String.format("%.2f %s", entry.getValue(), ingredient.unitMeasure)
                            };
                        })
                        .toArray(String[][]::new),
                new String[] { "Ingredient", "Amount" }));
        ingredientsTablePane.setPreferredSize(TableSize.MEDIUM.dimension);

        constraints.gridy++;
        constraints.weightx = 1;
        constraints.weighty = 1;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.insets.top = constraints.insets.bottom;
        constraints.insets.bottom = 20;

        panel.add(ingredientsTablePane, constraints);

        for (int i = 0; i < transactions.size(); i++) {
            constraints.gridy++;
            constraints.insets.top = 0;
            constraints.insets.bottom = 0;

            panel.add(new JSeparator(SwingConstants.HORIZONTAL), constraints);

            constraints.gridy++;
            constraints.weightx = 0;
            constraints.weighty = 0;
            constraints.fill = GridBagConstraints.HORIZONTAL;
            constraints.insets.top = 12;
            constraints.insets.bottom = 2;

            panel.add(new JLabel("Transaction #: " + (i + 1)), constraints);

            Transaction transaction = transactions.get(i);

            constraints.gridy++;
            constraints.insets.top = constraints.insets.bottom;

            panel.add(new JLabel("Truck ID: " + transaction.truck.id), constraints);

            constraints.gridy++;

            panel.add(new JLabel("Coffee: " + transaction.coffeeName), constraints);

            constraints.gridy++;

            panel.add(new JLabel("Total Cost: " + transaction.toCostString()), constraints);

            constraints.gridy++;
            constraints.fill = GridBagConstraints.NONE;
            constraints.insets.top = 4;

            panel.add(new JLabel("Ingredients"), constraints);

            ingredientsTablePane = new JScrollPane(new IngredientsTable(transaction));
            ingredientsTablePane.setPreferredSize(TableSize.SMALL.dimension);

            constraints.gridy++;
            constraints.weightx = 1;
            constraints.weighty = 1;
            constraints.fill = GridBagConstraints.BOTH;
            constraints.insets.top = constraints.insets.bottom;
            constraints.insets.bottom = constraints.insets.left;

            panel.add(ingredientsTablePane, constraints);
        }

        add(new JScrollPane(panel));

        setMaximumSize(new Dimension(getSize().width, 660));
        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }
}
