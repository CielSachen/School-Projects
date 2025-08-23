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
import java.util.List;
import java.util.Scanner;

import cielsachen.javajeeps.mco1.helper.ExceptionMessage;
import cielsachen.javajeeps.mco1.helper.Input;
import cielsachen.javajeeps.mco1.helper.PrintColor;
import cielsachen.javajeeps.mco1.model.Ingredient;
import cielsachen.javajeeps.mco1.model.StorageBin;
import cielsachen.javajeeps.mco1.model.Truck;
import cielsachen.javajeeps.mco1.service.StorageBinService;
import cielsachen.javajeeps.mco1.service.TruckService;
import cielsachen.javajeeps.mco1.util.Output;

/** Represents a controller for interacting with trucks. */
public class TruckController {
    private final Scanner scanner;
    private final Input input;

    private final TruckService service;
    private final StorageBinService storageBinService;

    /**
     * Creates and returns a new {@code TruckController} object instance.
     *
     * @param service           The truck service to use.
     * @param storageBinService The storage bin service to use.
     * @param scanner           The console input scanner to use.
     * @param input             The CLI input helper to use.
     */
    public TruckController(TruckService service, StorageBinService storageBinService, Scanner scanner, Input input) {
        this.scanner = scanner;
        this.input = input;

        this.service = service;
        this.storageBinService = storageBinService;
    }

    /**
     * Creates a new truck and adds it to the system.
     *
     * @return A new truck.
     */
    public Truck createTruck() {
        Output.printHeader2("Create a New Truck");

        String givenLoc;

        while (true) {
            System.out.println();

            System.out.print("Where will this truck be located? ");

            givenLoc = scanner.nextLine();

            if (service.isOccupiedLocation(givenLoc)) {
                System.out.println();

                ExceptionMessage.printCustom("A truck already exists on this location!");

                continue;
            }

            break;
        }

        boolean isSpecial = input.getBoolean(
                "Is this truck a special coffee truck " + PrintColor.set("(true/false)", PrintColor.RED) + "?");

        var truck = new Truck(service.getTrucks().size() + 1, givenLoc, isSpecial);

        service.addTruck(truck);

        System.out.println();

        Output.printHeader2("Set Storage Bin Ingredients");

        Ingredient[] regularIngredients = Ingredient.regularValues();
        Ingredient[] specialIngredients = Ingredient.specialValues();

        for (int storageBinId = 1; storageBinId <= (isSpecial
                ? StorageBin.SPECIAL_TRUCK_COUNT
                : StorageBin.STANDARD_TRUCK_COUNT); storageBinId++) {
            while (true) {
                try {
                    System.out.println();

                    for (StorageBin storageBin : storageBinService.getStorageBinsByTruck(truck)) {
                        System.out.println(PrintColor.set("Bin #" + storageBin.id + " = " + storageBin.getIngredient(),
                                PrintColor.BRIGHT_GREEN));
                    }

                    System.out.println("Bin #" + storageBinId + " =");

                    System.out.println();

                    System.out.println("What item should this storage bin contain?");

                    Ingredient[] ingredients = storageBinId <= StorageBin.STANDARD_TRUCK_COUNT
                            ? regularIngredients
                            : specialIngredients;

                    for (int i = 0; i < ingredients.length; i++) {
                        System.out.println("  [" + (i + 1) + "] " + ingredients[i]);
                    }

                    System.out.println();

                    System.out.print("  > ");

                    int chosenIngredientIdx = scanner.nextInt() - 1;

                    scanner.nextLine();

                    if (chosenIngredientIdx >= 0 && chosenIngredientIdx < ingredients.length) {
                        storageBinService
                                .addStorageBin(new StorageBin(storageBinId, truck, ingredients[chosenIngredientIdx]));

                        break;
                    }

                    System.out.println();

                    ExceptionMessage.INVALID_INTEGER_CHOICE.print();
                } catch (InputMismatchException e) {
                    scanner.nextLine();

                    System.out.println();

                    ExceptionMessage.INVALID_INTEGER_CHOICE.print();
                }
            }
        }

        System.out.println();

        System.out.println(PrintColor.set("Created a new coffee truck!", PrintColor.BRIGHT_GREEN));

        System.out.println();

        System.out.println(PrintColor.set("Deployed the coffee truck to" + givenLoc + "!", PrintColor.BRIGHT_GREEN));

        return truck;
    }

    /**
     * Moves a truck to a new unoccupied location.
     *
     * @param truck The truck to move.
     */
    public void relocateTruck(Truck truck) {
        String givenLoc;

        while (true) {
            System.out.print("Where will this truck be relocated to? ");

            givenLoc = scanner.nextLine();

            System.out.println();

            if (service.isOccupiedLocation(givenLoc)) {
                ExceptionMessage.printCustom("A truck already exists on this location!");

                System.out.println();

                continue;
            }

            break;
        }

        truck.setLocation(givenLoc);

        System.out.println(PrintColor.set("Relocated the coffee truck to " + givenLoc + "!", PrintColor.BRIGHT_GREEN));
    }

    /**
     * Restocks, empties, or changes the ingredient of a truck's storage bin.
     *
     * @param truck The truck to update a storage bin of.
     */
    public void updateStorageBins(Truck truck) {
        while (true) {
            Output.printHeader2("Update Storage Bins");

            List<StorageBin> storageBins = storageBinService.getStorageBinsByTruck(truck);

            StorageBin chosenStorageBin = null;

            while (true) {
                try {
                    System.out.println();

                    System.out.println("Which storage bin would you like to update?");

                    for (StorageBin storageBin : storageBins) {
                        System.out.println("  [" + storageBin.id + "] " + storageBin.getIngredient().name + " ("
                                + PrintColor.set(storageBin.toCapacityString(),
                                        storageBin.isCriticalCapacity() ? PrintColor.RED : PrintColor.BRIGHT_GREEN)
                                + ")");
                    }

                    System.out.println();
                    System.out.println("  [X] Return");

                    System.out.println();

                    System.out.print("  > ");

                    int chosenStorageBinId = scanner.nextInt();

                    scanner.nextLine();

                    if (chosenStorageBinId >= 0 && chosenStorageBinId < storageBins.size()) {
                        chosenStorageBin = storageBinService.getStorageBinById(chosenStorageBinId, truck).get();

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

            if (chosenStorageBin == null) {
                return;
            }

            System.out.println();

            Output.printHeader2("Update Bin " + chosenStorageBin.id);

            double currentCapacity = chosenStorageBin.getCapacity();
            Ingredient currentIngredient = chosenStorageBin.getIngredient();

            while (true) {
                try {
                    System.out.println();

                    System.out.println("What would you like to do to the storage bin?");

                    if (currentCapacity < currentIngredient.maxCapacity) {
                        System.out.println("  [R] Restock (" + PrintColor.set("+(1+)", PrintColor.BRIGHT_GREEN) + ")");
                    }

                    if (currentCapacity > 0) {
                        System.out.println("  [E] Empty ("
                                + PrintColor.set(String.format("-%.2f", currentCapacity), PrintColor.RED) + ")");
                    }

                    System.out.println("  [C] Change Ingredients");
                    System.out.println();
                    System.out.println("  [X] Return");

                    System.out.println();

                    System.out.print("  > ");

                    char chosenOptionId = input.getCharacter();

                    switch (chosenOptionId) {
                        case 'R':
                            if (currentCapacity == currentIngredient.maxCapacity) {
                                ExceptionMessage.printCustom("The storage bin is already full!");

                                break;
                            }

                            Ingredient storageBinIngredient = chosenStorageBin.getIngredient();

                            float additionalCapacity;

                            while (true) {
                                additionalCapacity = input.getFloat("How much ("
                                        + PrintColor.set(storageBinIngredient.unitMeasure, PrintColor.YELLOW) + ") "
                                        + PrintColor.set(storageBinIngredient.name, PrintColor.YELLOW)
                                        + " should be restocked? ", true);

                                if (additionalCapacity > 0) {
                                    if (currentCapacity + additionalCapacity > currentIngredient.maxCapacity) {
                                        chosenStorageBin.decreaseCapacity(currentCapacity);
                                        chosenStorageBin.increaseCapacity(currentIngredient.maxCapacity);
                                    } else {
                                        chosenStorageBin.increaseCapacity(additionalCapacity);
                                    }

                                    break;
                                }

                                System.out.println();

                                ExceptionMessage.printCustom("Please only input a positive floating point number!");
                            }

                            System.out.println(
                                    PrintColor.set("The storage bin has been restocked!", PrintColor.BRIGHT_GREEN));

                            break;
                        case 'E':
                            if (currentCapacity == 0) {
                                ExceptionMessage.printCustom("The storage bin is already empty!");

                                break;
                            }

                            chosenStorageBin.decreaseCapacity(currentCapacity);

                            System.out.println(
                                    PrintColor.set("The storage bin has been emptied!", PrintColor.BRIGHT_GREEN));

                            break;
                        case 'C': {
                            Ingredient[] ingredients = chosenStorageBin.id <= StorageBin.STANDARD_TRUCK_COUNT
                                    ? Ingredient.regularValues()
                                    : Ingredient.specialValues();

                            while (true) {
                                try {
                                    System.out.println();

                                    for (StorageBin storageBin : storageBinService.getStorageBinsByTruck(truck)) {
                                        if (!storageBin.equals(chosenStorageBin)) {
                                            System.out.println(PrintColor.set(
                                                    "Bin #" + storageBin.id + " = " + storageBin.getIngredient().name,
                                                    PrintColor.BRIGHT_CYAN));
                                        }
                                    }

                                    System.out.println();

                                    System.out.println(
                                            "Bin #" + chosenStorageBin.id + " = " + currentIngredient.name);

                                    System.out.println();

                                    System.out.println("What item should this storage bin contain instead?");

                                    for (int i = 0; i < ingredients.length; i++) {
                                        Ingredient ingredient = ingredients[i];

                                        if (!ingredient.equals(currentIngredient)) {
                                            System.out.println("  [" + (i + 1) + "] " + ingredient.name);
                                        }
                                    }

                                    System.out.println();

                                    System.out.print("  > ");

                                    int chosenIngredientIdx = scanner.nextInt() - 1;

                                    scanner.nextLine();

                                    if (chosenIngredientIdx >= 0 && chosenIngredientIdx < ingredients.length) {
                                        Ingredient chosenIngredient = ingredients[chosenIngredientIdx];

                                        if (!chosenIngredient.equals(currentIngredient)) {
                                            chosenStorageBin.setIngredient(chosenIngredient);

                                            if (currentCapacity > 0) {
                                                chosenStorageBin.decreaseCapacity(currentCapacity);
                                            }

                                            chosenStorageBin.increaseCapacity(chosenIngredient.maxCapacity);

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

                            break;
                        }
                        case 'X':
                            break;
                        default:
                            System.out.println();

                            ExceptionMessage.INVALID_CHARACTER_CHOICE.print();

                            continue;
                    }

                    break;
                } catch (InputMismatchException e) {
                    scanner.nextLine();

                    System.out.println();

                    ExceptionMessage.INVALID_CHARACTER_CHOICE.print();
                }
            }

            System.out.println();
        }
    }

    /** Prints the information summary of all deployed trucks. */
    public void printTrucksInfo() {
        Output.printHeader1("All Trucks Info Summary");

        System.out.println();

        System.out.println("Number of Trucks Deployed: "
                + PrintColor.set(Integer.toString(service.getTrucks().size()), PrintColor.BRIGHT_GREEN) + " ("
                + PrintColor.set(service.getSpecialTrucks().size() + " Special", PrintColor.BRIGHT_YELLOW) + ")");

        System.out.println();

        System.out.println("Ingredients:");

        for (Ingredient ingredient : Ingredient.values()) {
            System.out.println("  " + ingredient + ": " + PrintColor.set(
                    String.format("%.2f",
                            this.storageBinService.getStorageBinsByIngredient(ingredient).stream()
                                    .mapToDouble((sb) -> sb.getCapacity()).sum())
                            + " " + ingredient.unitMeasure,
                    PrintColor.BRIGHT_CYAN));
        }
    }

    /**
     * Prints the information summary of a truck.
     *
     * @param truck The truck to print get the info from.
     */
    public void printTruckInfo(Truck truck) {
        Output.printHeader1("Truck " + truck.id + " Info Summary");

        System.out.println();

        System.out.println("Special Truck: " + (truck.isSpecial
                ? PrintColor.set("Yes", PrintColor.BRIGHT_GREEN)
                : PrintColor.set("No", PrintColor.RED)));
        System.out.println("Location: " + PrintColor.set(truck.getLocation(), PrintColor.BRIGHT_CYAN));

        System.out.println();

        System.out.println("Storage Bins:");

        for (StorageBin storageBin : storageBinService.getStorageBinsByTruck(truck)) {
            System.out.println("  Bin " + storageBin.id + " = "
                    + PrintColor.set(storageBin.getIngredient().name, PrintColor.BRIGHT_CYAN) + " ("
                    + PrintColor.set(storageBin.toCapacityString(), storageBin.isCriticalCapacity()
                            ? PrintColor.RED
                            : PrintColor.BRIGHT_GREEN)
                    + ")");
        }
    }
}
