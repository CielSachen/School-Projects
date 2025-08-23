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

package cielsachen.javajeeps.mco1.controller;

import java.util.InputMismatchException;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Scanner;

import cielsachen.javajeeps.mco1.exception.InsufficientCapacityException;
import cielsachen.javajeeps.mco1.helper.ExceptionMessage;
import cielsachen.javajeeps.mco1.helper.Input;
import cielsachen.javajeeps.mco1.helper.PrintColor;
import cielsachen.javajeeps.mco1.model.Ingredient;
import cielsachen.javajeeps.mco1.model.Transaction;
import cielsachen.javajeeps.mco1.model.Truck;
import cielsachen.javajeeps.mco1.model.coffee.Coffee;
import cielsachen.javajeeps.mco1.model.coffee.CoffeeSize;
import cielsachen.javajeeps.mco1.model.coffee.EspressoRatio;
import cielsachen.javajeeps.mco1.service.CoffeeService;
import cielsachen.javajeeps.mco1.service.StorageBinService;
import cielsachen.javajeeps.mco1.service.TransactionService;
import cielsachen.javajeeps.mco1.util.Output;

/** Represents a controller for interacting with coffees. */
public class CoffeeController {
    private final Scanner scanner;
    private final Input input;

    private final CoffeeService service;
    private final StorageBinService storageBinService;
    private final TransactionService transactionService;

    /**
     * Creates and returns a new {@code CoffeeController} object instance.
     *
     * @param service            The coffee service to use.
     * @param storageBinService  The storage bin service to use.
     * @param transactionService The transaction service to use.
     * @param scanner            The console input scanner to use.
     * @param input              The CLI input helper to use.
     */
    public CoffeeController(CoffeeService service, StorageBinService storageBinService,
            TransactionService transactionService, Scanner scanner, Input input) {
        this.service = service;
        this.input = input;

        this.scanner = scanner;
        this.storageBinService = storageBinService;
        this.transactionService = transactionService;
    }

    /**
     * Checks whether a truck can brew any coffee. This wraps the {@link CoffeeService#isCapableOfBrewing
     * isCapableOfBrewing()} method.
     *
     * @param truck The truck to check.
     * @return Whether the truck can brew any coffee.
     */
    public boolean isCapableOfBrewing(Truck truck) {
        return service.isCapableOfBrewing(truck);
    }

    /**
     * Checks whether the prices of the coffees and add-ons have been set. This wraps {@link CoffeeService#isPricesSet
     * isPricesSet()} the method.
     *
     * @return Whether the prices of the coffees and add-ons are not equal to {@link Coffee#DEFAULT_PRICE}.
     */
    public boolean isPricesSet() {
        return service.isPricesSet();
    }

    /** Updates the prices of all coffees and add-ons. */
    public void updatePrices() {
        Output.printHeader2("Change the Coffee Prices");

        System.out.println();

        for (Coffee coffee : service.getCoffees()) {
            while (true) {
                boolean isPriceSet = coffee.setPrice(input.getFloat("What base price should "
                        + PrintColor.set(coffee.name + "s", PrintColor.YELLOW) + " should have?"));

                if (isPriceSet) {
                    break;
                }

                System.out.println();

                ExceptionMessage.printCustom("Only input a valid price (>= 0)!");

                System.out.println();
            }
        }

        service.espresso.setPrice(input.getFloat(
                "What price should " + PrintColor.set("extra espresso shots", PrintColor.YELLOW) + " should have?",
                true));
        service.syrup.setPrice(input.getFloat(
                "What base price should " + PrintColor.set("syrup add-ons", PrintColor.YELLOW) + " should have?"));
    }

    /**
     * Prepares coffee in a truck. This will decrease the capacities of relevant storage bins and create a new
     * {@link Transaction transaction}.
     *
     * @param truck The truck to prepare the coffee in.
     */
    public void prepareCoffee(Truck truck) {
        Output.printHeader2("Order a Coffee");

        Coffee[] coffees = service.getCoffeesByTruck(truck);

        Coffee chosenCoffee = null;

        while (true) {
            try {
                System.out.println();

                System.out.println("Which coffee would you like to order?");

                for (int i = 0; i < coffees.length; i++) {
                    Coffee coffee = coffees[i];

                    System.out.println("  [" + (i + 1) + "] " + coffee);
                }

                System.out.println();
                System.out.println("  [X] Return");

                System.out.println();

                System.out.print("  > ");

                int chosenCoffeeIdx = scanner.nextInt() - 1;

                scanner.nextLine();

                if (chosenCoffeeIdx >= 0 && chosenCoffeeIdx < coffees.length) {
                    chosenCoffee = coffees[chosenCoffeeIdx];

                    break;
                }

                System.out.println();

                ExceptionMessage.INVALID_INTEGER_CHOICE.print();
            } catch (InputMismatchException e) {
                if (input.getCharacter() == 'X') {
                    break;
                }

                System.out.println();

                ExceptionMessage.INVALID_INTEGER_CHOICE.print();
            }
        }

        if (chosenCoffee == null) {
            return;
        }

        System.out.println();

        CoffeeSize[] coffeeSizes = CoffeeSize.values();

        CoffeeSize chosenSize = null;

        while (true) {
            try {
                System.out.println();

                System.out.println("What size of " + chosenCoffee.name + " would you like?");

                for (int i = 0; i < coffeeSizes.length; i++) {
                    CoffeeSize size = coffeeSizes[i];

                    System.out
                            .println("  [" + (i + 1) + "] " + PrintColor.set(size.toString(), PrintColor.BRIGHT_CYAN));
                }

                System.out.println();

                System.out.print("  > ");

                int chosenSizeIdx = scanner.nextInt() - 1;

                scanner.nextLine();

                if (chosenSizeIdx >= 0 && chosenSizeIdx < coffeeSizes.length) {
                    chosenSize = coffeeSizes[chosenSizeIdx];

                    break;
                }

                System.out.println();

                ExceptionMessage.INVALID_CHARACTER_CHOICE.print();
            } catch (InputMismatchException e) {
                scanner.nextLine();

                System.out.println();

                ExceptionMessage.INVALID_CHARACTER_CHOICE.print();
            }
        }

        EspressoRatio[] espressoRatios = truck.isSpecial ? EspressoRatio.values() : EspressoRatio.regularValues();

        EspressoRatio chosenRatio = EspressoRatio.STANDARD;

        if (truck.isSpecial) {
            while (true) {
                try {
                    System.out.println();

                    System.out.println("What ratio of espresso would you like?");

                    for (int i = 0; i < espressoRatios.length; i++) {
                        EspressoRatio ratio = espressoRatios[i];

                        System.out.println(
                                "  [" + (i + 1) + "] " + PrintColor.set(ratio.toString(), PrintColor.BRIGHT_CYAN));
                    }

                    System.out.println();

                    System.out.print("  > ");

                    int chosenRatioIdx = scanner.nextInt() - 1;

                    scanner.nextLine();

                    if (chosenRatioIdx >= 0 && chosenRatioIdx < espressoRatios.length) {
                        chosenRatio = espressoRatios[chosenRatioIdx];

                        break;
                    }

                    System.out.println();

                    ExceptionMessage.INVALID_CHARACTER_CHOICE.print();
                } catch (InputMismatchException e) {
                    scanner.nextLine();

                    System.out.println();

                    ExceptionMessage.INVALID_CHARACTER_CHOICE.print();
                }
            }
        }

        if (chosenRatio.equals(EspressoRatio.CUSTOM)) {
            EspressoRatio.setCustomRatio(input.getInteger("What should the ratio of water to coffea beans be "
                    + PrintColor.set("(1 : ?)", PrintColor.YELLOW) + "?", true));
        }

        try {
            service.canBrewCoffee(truck, chosenCoffee, chosenSize, chosenRatio);

            Map<Ingredient, Double> ingredients = new LinkedHashMap<Ingredient, Double>(
                    service.brewCoffee(truck, chosenCoffee, chosenSize, chosenRatio));

            int extraEspressoShotsCnt = 0;
            float additionalCost = 0;

            if (truck.isSpecial) {
                boolean isAddingEspressoShots = input.getBoolean(
                        "Would you like to add extra shots of espresso "
                                + PrintColor.set("(true/false)", PrintColor.RED) + "?",
                        !chosenRatio.equals(EspressoRatio.CUSTOM));

                if (isAddingEspressoShots) {
                    EspressoRatio chosenShotsRatio = EspressoRatio.STANDARD;

                    if (truck.isSpecial) {
                        while (true) {
                            try {
                                System.out.println();

                                System.out.println("What ratio of espresso would you like?");

                                for (int i = 0; i < espressoRatios.length; i++) {
                                    EspressoRatio ratio = espressoRatios[i];

                                    System.out.println("  [" + (i + 1) + "] "
                                            + PrintColor.set(ratio.toString(), PrintColor.BRIGHT_CYAN));
                                }

                                System.out.println();

                                System.out.print("  > ");

                                int chosenRatioIdx = scanner.nextInt() - 1;

                                scanner.nextLine();

                                if (chosenRatioIdx >= 0 && chosenRatioIdx < espressoRatios.length) {
                                    chosenShotsRatio = espressoRatios[chosenRatioIdx];

                                    break;
                                }

                                System.out.println();

                                ExceptionMessage.INVALID_CHARACTER_CHOICE.print();
                            } catch (InputMismatchException e) {
                                scanner.nextLine();

                                System.out.println();

                                ExceptionMessage.INVALID_CHARACTER_CHOICE.print();
                            }
                        }
                    }

                    if (chosenShotsRatio.equals(EspressoRatio.CUSTOM)) {
                        EspressoRatio
                                .setCustomRatio(input.getInteger("What should the ratio of water to coffea beans be "
                                        + PrintColor.set("(1 : ?)", PrintColor.YELLOW) + "?", true));
                    }

                    extraEspressoShotsCnt = input.getInteger("How many extra shots should be added?");

                    try {
                        service.canBrewEspressoShots(truck, extraEspressoShotsCnt, chosenShotsRatio);

                        ingredients.putAll(service.brewEspressoShots(truck, extraEspressoShotsCnt, chosenShotsRatio));
                        additionalCost += service.espresso.getPrice() * extraEspressoShotsCnt;
                    } catch (InsufficientCapacityException e) {
                        System.out.println();

                        System.out.println(PrintColor.set("The truck does not have enough ", PrintColor.RED)
                                + PrintColor.set(e.ingredient.name, PrintColor.YELLOW)
                                + PrintColor.set("to brew the coffee.", PrintColor.RED));
                    }
                }

                boolean isAddingSyrups = true;

                Ingredient[] syrups = Ingredient.specialValues();

                while (isAddingSyrups) {
                    isAddingSyrups = input.getBoolean("Would you like to add pumps of syrup "
                            + PrintColor.set("(true/false)", PrintColor.RED) + "?");

                    if (isAddingSyrups) {
                        Ingredient chosenSyrup = null;

                        while (true) {
                            try {
                                System.out.println();

                                System.out.println("Which syrup would you like to add?");

                                for (int i = 0; i < syrups.length; i++) {
                                    Ingredient ingredient = syrups[i];

                                    if (storageBinService.truckHasIngredient(truck, ingredient)) {
                                        System.out.println("  [" + (i + 1) + "] " + ingredient);
                                    }
                                }

                                System.out.println();

                                System.out.print("  > ");

                                int chosenSyrupIndex = scanner.nextInt() - 1;

                                scanner.nextLine();

                                if (chosenSyrupIndex >= 0 && chosenSyrupIndex < syrups.length) {
                                    chosenSyrup = syrups[chosenSyrupIndex];

                                    if (storageBinService.truckHasIngredient(truck, chosenSyrup)) {
                                        break;
                                    }
                                }

                                System.out.println();

                                ExceptionMessage.INVALID_INTEGER_CHOICE.print();
                            } catch (InputMismatchException e) {
                                scanner.nextLine();

                                System.out.println();

                                ExceptionMessage.INVALID_INTEGER_CHOICE.print();
                            }
                        }

                        int amount = input.getInteger("How many pumps should be added?", true);

                        try {
                            service.canAddSyrup(truck, chosenSyrup, amount);

                            ingredients.putAll(service.addSyrup(truck, chosenSyrup, amount));
                            additionalCost += service.syrup.getPrice() * amount;
                        } catch (InsufficientCapacityException e) {
                            System.out.println();

                            System.out.println(PrintColor.set("The truck does not have enough ", PrintColor.RED)
                                    + PrintColor.set(e.ingredient.name, PrintColor.YELLOW)
                                    + PrintColor.set("to brew the coffee.", PrintColor.RED));
                        }
                    }
                }
            }

            System.out.println();

            System.out.println(">>> Preparing a " + PrintColor.set(chosenSize.toString(), PrintColor.YELLOW) + " of "
                    + PrintColor.set(chosenCoffee.name, PrintColor.YELLOW) + " with "
                    + PrintColor.set(Integer.toString(extraEspressoShotsCnt), PrintColor.BRIGHT_CYAN)
                    + PrintColor.set(" extra shots of espresso...", PrintColor.YELLOW));
            System.out.println(">>> Brewing " + PrintColor.set(chosenRatio.name + " Espresso", PrintColor.YELLOW));

            for (Map.Entry<Ingredient, Double> entry : ingredients.entrySet()) {
                Ingredient ingredient = entry.getKey();

                System.out.println(">>> Adding " + PrintColor.set(ingredient.name, PrintColor.YELLOW) + " ("
                        + PrintColor.set(String.format("%.2f %s", entry.getValue(), ingredient.unitMeasure),
                                PrintColor.BRIGHT_CYAN)
                        + ")...");
            }

            System.out.println(">>> The " + chosenCoffee + " is done!");

            System.out.println();

            float totalCost = chosenCoffee.getPrice() + additionalCost;

            System.out.println("The " + PrintColor.set(chosenSize.toString(), PrintColor.YELLOW) + " of "
                    + PrintColor.set(chosenCoffee.name, PrintColor.YELLOW) + " will cost "
                    + PrintColor.set(totalCost + " PHP", PrintColor.BRIGHT_GREEN) + ".");

            transactionService.addTransaction(new Transaction(chosenCoffee.name, chosenSize, totalCost, truck,
                    extraEspressoShotsCnt, ingredients));
        } catch (InsufficientCapacityException e) {
            System.out.println();

            System.out.println(PrintColor.set("The truck does not have enough ", PrintColor.RED)
                    + PrintColor.set(e.ingredient.name, PrintColor.YELLOW)
                    + PrintColor.set("to brew the coffee.", PrintColor.RED));
        }
    }

    /**
     * Prints the prices of all coffees and add-ons.
     *
     * @param truck The truck to print the prices of.
     */
    public void printPrices(Truck truck) {
        Output.printHeader3("Coffee and Add-On Prices");

        System.out.println();

        System.out.println("Coffees:");

        for (Coffee coffee : service.getCoffeesByTruck(truck)) {
            System.out.println("  " + coffee + " = " + PrintColor.set(coffee.toPriceString(), PrintColor.BRIGHT_GREEN));
        }

        if (truck.isSpecial) {
            System.out.println();

            System.out.println("Add-Ons:");

            if (storageBinService.truckHasIngredient(truck, Ingredient.COFFEE_BEANS, Ingredient.WATER)) {
                System.out.println("  Extra Espresso Shots = "
                        + PrintColor.set(service.espresso.toPriceString(), PrintColor.BRIGHT_GREEN));
            }

            if (storageBinService.truckHasSyrups(truck)) {
                System.out.println(
                        "  Syrup Add-Ons = " + PrintColor.set(service.syrup.toPriceString(), PrintColor.BRIGHT_GREEN));
            }
        }
    }
}
