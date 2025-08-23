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

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTable;
import javax.swing.SwingConstants;

import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.Product;
import cielsachen.javajeeps.mco2.model.StorageBin;
import cielsachen.javajeeps.mco2.model.Transaction;
import cielsachen.javajeeps.mco2.model.Truck;
import cielsachen.javajeeps.mco2.model.coffee.Coffee;
import cielsachen.javajeeps.mco2.view.component.CoffeePricesTable;
import cielsachen.javajeeps.mco2.view.component.IngredientsTable;
import cielsachen.javajeeps.mco2.view.component.TableSize;

/** Represents the window containing information about a truck. */
public class TruckView extends JFrame {
    /**
     * Creates and returns a new {@code TruckView} object instance.
     *
     * @param parentComp   The parent component of the window.
     * @param truck        The truck to use.
     * @param storageBins  The list of storage bins of the truck to use.
     * @param coffees      The coffees the truck to use can brew.
     * @param espresso     The addable extra espresso shot.
     * @param syrup        The addable syrup add-on.
     * @param transactions The list of transactions linked with the truck to use.
     */
    public TruckView(Component parentComp, Truck truck, List<StorageBin> storageBins, Coffee[] coffees,
            Product espresso, Product syrup, List<Transaction> transactions) {
        super("Truck #" + truck.id);

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        var panel = new JPanel(new GridBagLayout());

        var constraints = new GridBagConstraints();
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets = new Insets(20, 20, 2, 20);

        panel.add(new JLabel("ID: " + truck.id), constraints);

        constraints.gridy++;
        constraints.insets.top = constraints.insets.bottom;

        panel.add(new JLabel("Special Truck: " + (truck.isSpecial ? "Yes" : "No")), constraints);

        constraints.gridy++;

        panel.add(new JLabel("Location: " + truck.getLocation()), constraints);

        constraints.gridy++;
        constraints.fill = GridBagConstraints.NONE;
        constraints.insets.top = 4;

        panel.add(new JLabel("Storage Bins"), constraints);

        var storageBinsTablePane = new JScrollPane(new JTable(storageBins
                .stream()
                .map((storageBin) -> {
                    Ingredient ingredient = storageBin.getIngredient();

                    return new String[] {
                            Integer.toString(storageBin.id),
                            ingredient.name,
                            String.format("%.2f %s", storageBin.getCapacity(), ingredient.unitMeasure),
                            String.format("%.2f %s", ingredient.maxCapacity, ingredient.unitMeasure)
                    };
                })
                .toArray(String[][]::new),
                new String[] { "ID", "Ingredient", "Current Capacity", "Maximum Capacity" }));
        storageBinsTablePane.setPreferredSize(TableSize.LARGE.dimension);

        constraints.gridy++;
        constraints.weightx = 1;
        constraints.weighty = 1;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.insets.top = constraints.insets.bottom;
        constraints.insets.bottom = 20;

        panel.add(storageBinsTablePane, constraints);

        if (coffees != null && espresso != null && syrup != null) {
            constraints.gridy++;
            constraints.insets.top = 0;
            constraints.insets.bottom = 0;

            panel.add(new JSeparator(SwingConstants.HORIZONTAL), constraints);

            constraints.gridy++;
            constraints.weightx = 0;
            constraints.weighty = 0;
            constraints.fill = GridBagConstraints.NONE;
            constraints.insets.top = 12;
            constraints.insets.bottom = 2;

            panel.add(new JLabel("Prices"), constraints);

            var coffeePricesTablePane = new JScrollPane(new CoffeePricesTable(coffees));
            coffeePricesTablePane.setPreferredSize(TableSize.LARGE.dimension);

            constraints.gridy++;
            constraints.weightx = 1;
            constraints.weighty = 1;
            constraints.fill = GridBagConstraints.BOTH;
            constraints.insets.top = constraints.insets.bottom;

            if (!truck.isSpecial) {
                constraints.insets.bottom = 20;
            }

            panel.add(coffeePricesTablePane, constraints);

            if (truck.isSpecial) {
                constraints.gridy++;
                constraints.weightx = 0;
                constraints.weighty = 0;
                constraints.fill = GridBagConstraints.NONE;

                panel.add(new JLabel("Extra Espresso Shots: " + espresso.toPriceString()), constraints);

                constraints.gridy++;
                constraints.insets.bottom = 20;

                panel.add(new JLabel("Add-On Syrups: " + syrup.toPriceString()), constraints);
            }
        }

        if (transactions != null) {
            constraints.weightx = 1;
            constraints.weighty = 1;
            constraints.fill = GridBagConstraints.BOTH;

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

                panel.add(new JLabel("Coffee: " + transaction.coffeeName), constraints);

                constraints.gridy++;

                panel.add(new JLabel("Total Cost: " + transaction.toCostString()), constraints);

                constraints.gridy++;
                constraints.fill = GridBagConstraints.NONE;
                constraints.insets.top = 4;

                panel.add(new JLabel("Ingredients"), constraints);

                var ingredientsTablePane = new JScrollPane(new IngredientsTable(transaction));
                ingredientsTablePane.setPreferredSize(TableSize.SMALL.dimension);

                constraints.gridy++;
                constraints.weightx = 1;
                constraints.weighty = 1;
                constraints.fill = GridBagConstraints.BOTH;
                constraints.insets.top = constraints.insets.bottom;
                constraints.insets.bottom = 20;

                panel.add(ingredientsTablePane, constraints);
            }
        }

        add(new JScrollPane(panel));

        setMaximumSize(new Dimension(getSize().width, 660));
        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }

    /**
     * Creates and returns a new {@code TruckView} object instance.
     *
     * @param parentComp  The parent component of the window.
     * @param truck       The truck to use.
     * @param storageBins The storage bins of the truck to use.
     * @param coffees     The coffees the truck to use can brew.
     * @param espresso    The addable extra espresso shot.
     * @param syrup       The addable syrup add-on.
     */
    public TruckView(Component parentComp, Truck truck, List<StorageBin> storageBins, Coffee[] coffees,
            Product espresso, Product syrup) {
        this(parentComp, truck, storageBins, coffees, espresso, syrup, null);
    }

    /**
     * Creates and returns a new {@code TruckView} object instance.
     *
     * @param parentComp  The parent component of the window.
     * @param truck       The truck to use.
     * @param storageBins The storage bins of the truck to use.
     */
    public TruckView(Component parentComp, Truck truck, List<StorageBin> storageBins) {
        this(parentComp, truck, storageBins, null, null, null);
    }
}
