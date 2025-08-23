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

package cielsachen.javajeeps.mco2.controller;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import javax.swing.JOptionPane;

import cielsachen.javajeeps.mco2.exception.InsufficientCapacityException;
import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.Transaction;
import cielsachen.javajeeps.mco2.model.Truck;
import cielsachen.javajeeps.mco2.model.coffee.Coffee;
import cielsachen.javajeeps.mco2.model.coffee.CoffeeSize;
import cielsachen.javajeeps.mco2.model.coffee.EspressoRatio;
import cielsachen.javajeeps.mco2.service.CoffeeService;
import cielsachen.javajeeps.mco2.service.StorageBinService;
import cielsachen.javajeeps.mco2.service.TransactionService;
import cielsachen.javajeeps.mco2.view.BrewCompletionView;
import cielsachen.javajeeps.mco2.view.component.Modal;
import cielsachen.javajeeps.mco2.view.form.PriceConfigurationForm;

/** Represents a controller for handling coffees. */
public class CoffeeController {
    private final CoffeeService service;
    private final StorageBinService storageBinService;
    private final TransactionService transactionService;

    private int extraEspressoShotsCnt;
    private float additionalCost;

    /**
     * Creates and returns a new {@code CoffeeController} object instance.
     *
     * @param service            The coffee service to use.
     * @param storageBinService  The storage bin service to use.
     * @param transactionService The transaction service to use.
     */
    public CoffeeController(CoffeeService service, StorageBinService storageBinService,
            TransactionService transactionService) {
        this.service = service;
        this.storageBinService = storageBinService;
        this.transactionService = transactionService;
    }

    /**
     * Updates the prices of all coffees and add-ons.
     *
     * @param parentComp The parent component of the windows to be shown.
     */
    public void updatePrices(Component parentComp) {
        Coffee[] coffees = service.getCoffees();

        var priceConfigForm = new PriceConfigurationForm(parentComp, coffees);

        priceConfigForm.submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                List<Float> prices;

                try {
                    prices = priceConfigForm.priceFields.stream().map((pf) -> Float.parseFloat(pf.getText())).toList();
                } catch (NumberFormatException e) {
                    Modal.showErrorDialog(priceConfigForm, "All fields must be filled!", "Missing Fields");

                    return;
                }

                int i;

                for (i = 0; i < coffees.length; i++) {
                    coffees[i].setPrice(prices.get(i));
                }

                service.espresso.setPrice(prices.get(i));
                service.syrup.setPrice(prices.get(i + 1));
            }
        });
    }

    /**
     * Prepares coffee in a truck. This will decrease the capacities of relevant storage bins and create a new
     * {@link Transaction transaction}.
     *
     * @param parentComp The parent component of the windows to be shown.
     * @param truck      The truck to prepare the coffee in.
     */
    public void prepareCoffee(Component parentComp, Truck truck) {
        Coffee[] coffees = service.getCoffeesByTruck(truck);

        Coffee selectedCoffee = Modal.showSelectionDialog(parentComp, "Please select a coffee to brew…",
                "Coffee Selection", coffees, coffees[0]);

        if (selectedCoffee == null) {
            return;
        }

        CoffeeSize[] coffeeSizes = CoffeeSize.values();

        CoffeeSize selectedSize = Modal.showSelectionDialog(parentComp, "Please select the size of the coffee to brew…",
                "Coffee Size Selection", coffeeSizes, coffeeSizes[0]);

        if (!truck.isSpecial) {
            brewCoffee(parentComp, truck, selectedCoffee, selectedSize, EspressoRatio.STANDARD);

            return;
        }

        EspressoRatio[] espressoRatios = truck.isSpecial ? EspressoRatio.values() : EspressoRatio.regularValues();

        EspressoRatio selectedRatio = Modal.showSelectionDialog(parentComp,
                "Please select the size of the coffee to brew…", "Coffee Size Selection", espressoRatios,
                espressoRatios[0]);

        if (selectedRatio.equals(EspressoRatio.CUSTOM)) {
            int waterRatio;

            while (true) {
                String givenWaterRatio = Modal.showInputDialog(parentComp,
                        "Please input the ratio of water to coffee beans…", "Espresso Ratio");

                if (givenWaterRatio == null) {
                    return;
                }

                try {
                    waterRatio = Integer.parseInt(givenWaterRatio);

                    break;
                } catch (NumberFormatException e) {
                    Modal.showErrorDialog(parentComp, "Please only input a whole number!", "Invalid Input");
                }
            }

            EspressoRatio.setCustomRatio(waterRatio);

            brewCoffee(parentComp, truck, selectedCoffee, selectedSize, selectedRatio);

            return;
        }

        brewCoffee(parentComp, truck, selectedCoffee, selectedSize, selectedRatio);
    }

    private void addEspressoShots(Component parentComp, Truck truck, EspressoRatio ratio,
            Map<Ingredient, Double> ingredientToAmount) {
        try {
            service.canBrewEspressoShots(truck, extraEspressoShotsCnt, ratio);

            ingredientToAmount.putAll(service.brewEspressoShots(truck, extraEspressoShotsCnt, ratio));
            additionalCost += service.espresso.getPrice() * extraEspressoShotsCnt;
        } catch (InsufficientCapacityException e) {
            Modal.showErrorDialog(parentComp, e.getMessage(), "Insufficient Ingredient");
        }
    }

    private void addSyrup(Component parentComp, Truck truck, Map<Ingredient, Double> ingredientToAmount) {
        int isAddingSyrups = Modal.showConfirmDialog(parentComp, "Would you like to add pumps of syrup?",
                "Add-On Syrup");

        if (isAddingSyrups == JOptionPane.YES_OPTION) {
            List<Ingredient> syrups = storageBinService
                    .getStorageBinsByTruck(truck)
                    .stream()
                    .map((sb) -> sb.getIngredient()).filter((i) -> i.isSpecial)
                    .toList();

            Ingredient selectedSyrup = Modal.showSelectionDialog(parentComp, "How many extra shots should be added?",
                    "Add-On Syrup", syrups, syrups.getFirst());

            if (selectedSyrup == null) {
                return;
            }

            int syrupCnt = 0;

            while (true) {
                String givenCnt = Modal.showInputDialog(parentComp, "How many pumps should be added?", "Add-On Syrup");

                if (givenCnt == null) {
                    return;
                }

                try {
                    syrupCnt = Integer.parseInt(givenCnt);

                    break;
                } catch (NumberFormatException e) {
                    Modal.showErrorDialog(parentComp, "Please only input a whole number!", "Invalid Input");
                }
            }

            try {
                service.canAddSyrup(truck, selectedSyrup, syrupCnt);

                ingredientToAmount.putAll(service.addSyrup(truck, selectedSyrup, syrupCnt));
                additionalCost += service.syrup.getPrice() * syrupCnt;
            } catch (InsufficientCapacityException e) {
                Modal.showErrorDialog(parentComp, e.getMessage(), "Insufficient Ingredient");
            }
        }
    }

    private void finishBrewing(Component parentComp, Truck truck, Coffee coffee, CoffeeSize size,
            EspressoRatio ratio, Map<Ingredient, Double> ingredientToAmount) {
        float totalCost = coffee.getPrice(size) + additionalCost;

        new BrewCompletionView(parentComp, coffee, ratio, size, extraEspressoShotsCnt, ingredientToAmount, totalCost);

        transactionService.addTransaction(
                new Transaction(coffee.name, size, totalCost, truck, extraEspressoShotsCnt, ingredientToAmount));
    }

    private void brewCoffee(Component parentComp, Truck truck, Coffee coffee, CoffeeSize size,
            EspressoRatio ratio) {
        extraEspressoShotsCnt = 0;
        additionalCost = 0;

        try {
            service.canBrewCoffee(truck, coffee, size, ratio);

            Map<Ingredient, Double> ingredientToAmount = new LinkedHashMap<>(
                    service.brewCoffee(truck, coffee, size, ratio));

            EspressoRatio.setCustomRatio(0);

            if (!truck.isSpecial) {
                finishBrewing(parentComp, truck, coffee, size, ratio, ingredientToAmount);

                return;
            }

            int isAddingEspressoShots = Modal.showConfirmDialog(parentComp,
                    "Would you like to add extra shots of espresso?", "Extra Espresso Shots");

            if (isAddingEspressoShots == JOptionPane.YES_OPTION) {
                while (true) {
                    String givenCnt = Modal.showInputDialog(parentComp, "How many extra shots should be added?",
                            "Extra Espresso Shots");

                    if (givenCnt == null) {
                        break;
                    }

                    try {
                        extraEspressoShotsCnt = Integer.parseInt(givenCnt);

                        break;
                    } catch (NumberFormatException e) {
                        Modal.showErrorDialog(parentComp, "Please only input a whole number!", "Invalid Input");
                    }
                }

                if (extraEspressoShotsCnt > 0) {
                    EspressoRatio[] espressoRatios = EspressoRatio.values();

                    EspressoRatio selectedRatio = Modal.showSelectionDialog(parentComp,
                            "Please select the size of the coffee to brew…", "Coffee Size Selection", espressoRatios,
                            espressoRatios[0]);

                    if (selectedRatio.equals(EspressoRatio.CUSTOM)) {
                        int waterRatio;

                        while (true) {
                            String givenWaterRatio = Modal.showInputDialog(parentComp,
                                    "Please input the ratio of water to coffee beans…", "Espresso Ratio");

                            if (givenWaterRatio == null) {
                                return;
                            }

                            try {
                                waterRatio = Integer.parseInt(givenWaterRatio);

                                break;
                            } catch (NumberFormatException e) {
                                Modal.showErrorDialog(parentComp, "Please only input a whole number!", "Invalid Input");
                            }
                        }

                        EspressoRatio.setCustomRatio(waterRatio);

                        addEspressoShots(parentComp, truck, ratio, ingredientToAmount);

                        EspressoRatio.setCustomRatio(0);

                        if (storageBinService.truckHasSyrups(truck)) {
                            addSyrup(parentComp, truck, ingredientToAmount);
                        }

                        finishBrewing(parentComp, truck, coffee, size, ratio, ingredientToAmount);

                        return;
                    }

                    addEspressoShots(parentComp, truck, ratio, ingredientToAmount);

                    if (storageBinService.truckHasSyrups(truck)) {
                        addSyrup(parentComp, truck, ingredientToAmount);
                    }

                    finishBrewing(parentComp, truck, coffee, size, ratio, ingredientToAmount);

                    return;
                }
            }

            addSyrup(parentComp, truck, ingredientToAmount);

            finishBrewing(parentComp, truck, coffee, size, ratio, ingredientToAmount);
        } catch (InsufficientCapacityException e) {
            Modal.showErrorDialog(parentComp, e.getMessage(), "Insufficient Ingredient");
        }
    }
}
