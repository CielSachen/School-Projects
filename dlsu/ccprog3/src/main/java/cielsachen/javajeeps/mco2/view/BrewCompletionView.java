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
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Map;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;

import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.coffee.Coffee;
import cielsachen.javajeeps.mco2.model.coffee.CoffeeSize;
import cielsachen.javajeeps.mco2.model.coffee.EspressoRatio;
import cielsachen.javajeeps.mco2.view.component.IngredientsTable;
import cielsachen.javajeeps.mco2.view.component.TableSize;

/** Represents the window containing information about a brewed coffee. */
public class BrewCompletionView extends JFrame {
    /**
     * Creates and returns a new {@code BrewCompletionView} object instance.
     *
     * @param parentComp            The parent component of the window.
     * @param coffee                The brewed coffee.
     * @param ratio                 The espresso ratio of the brewed coffee.
     * @param size                  The size of the brewed coffee.
     * @param extraEspressoShotsCnt The number of extra espresso shots added.
     * @param ingredientToAmount    The ingredients used to brew the coffee mapped to their amounts.
     * @param totalCost             The total cost of purchasing the brewed coffee.
     */
    public BrewCompletionView(Component parentComp, Coffee coffee, EspressoRatio ratio, CoffeeSize size,
            int extraEspressoShotsCnt, Map<Ingredient, Double> ingredientToAmount, double totalCost) {
        super("Brewing Completed");

        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        setLayout(new GridBagLayout());

        var constraints = new GridBagConstraints();
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        constraints.insets = new Insets(20, 20, 2, 20);

        add(new JLabel("Prepared Coffee: " + coffee), constraints);

        constraints.gridy++;
        constraints.insets.top = constraints.insets.bottom;

        add(new JLabel("Size: " + size), constraints);

        constraints.gridy++;

        add(new JLabel("Espresso Ratio: " + ratio), constraints);

        constraints.gridy++;

        add(new JLabel("Extra Espresso Shots: " + extraEspressoShotsCnt), constraints);

        constraints.gridy++;

        add(new JLabel("With Syrup: " + ingredientToAmount.keySet().stream().anyMatch((i) -> i.isSpecial)),
                constraints);

        constraints.gridy++;

        add(new JLabel("Total Cost: " + totalCost + " PHP"), constraints);

        constraints.gridy++;
        constraints.fill = GridBagConstraints.NONE;
        constraints.insets.top = 4;

        add(new JLabel("Ingredients Used"), constraints);

        var ingredientsTablePane = new JScrollPane(new IngredientsTable(ingredientToAmount));
        ingredientsTablePane.setPreferredSize(TableSize.SMALL.dimension);

        constraints.gridy++;
        constraints.weightx = 1;
        constraints.weighty = 1;
        constraints.fill = GridBagConstraints.BOTH;
        constraints.insets.top = constraints.insets.bottom;
        constraints.insets.bottom = constraints.insets.left;

        add(ingredientsTablePane, constraints);

        pack();
        setResizable(false);

        setLocationRelativeTo(parentComp);
        setVisible(true);
    }
}
