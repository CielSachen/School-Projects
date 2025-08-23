package cielsachen.javajeeps.mco1.controller;

import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

import cielsachen.javajeeps.mco1.helper.ExceptionMessage;
import cielsachen.javajeeps.mco1.helper.Input;
import cielsachen.javajeeps.mco1.helper.PrintColor;
import cielsachen.javajeeps.mco1.model.Truck;
import cielsachen.javajeeps.mco1.service.TruckService;
import cielsachen.javajeeps.mco1.util.Output;

/** Represents a controller for handling the main menus. */
public class MenuController {
    private final Scanner scanner;
    private final Input input;

    private final TruckController truckController;
    private final CoffeeController coffeeController;
    private final TransactionController transactionController;

    private final TruckService truckService;

    /** Creates and returns a new {@code MenuController} object instance. */
    public MenuController(TruckController truckController, CoffeeController coffeeController,
            TransactionController transactionController, TruckService truckService, Scanner scanner, Input input) {
        this.scanner = scanner;
        this.input = input;

        this.truckController = truckController;
        this.coffeeController = coffeeController;
        this.transactionController = transactionController;

        this.truckService = truckService;
    }

    /** Prints the main menu application CLI. */
    public void printMainMenu() {
        boolean isExiting = false;

        while (!isExiting) {
            Output.printTitle("JavaJeeps: MCO1");

            System.out.println();

            System.out.println("What would you like to do?");
            System.out.println("  [C] Create a Coffee truck");
            System.out.println("  [S] Simulate");
            System.out.println("  [D] Dashboard");
            System.out.println();
            System.out.println("  [X] Exit");

            System.out.println();

            System.out.print("  > ");

            char chosenOptionId = input.getCharacter();

            switch (chosenOptionId) {
                case 'C': {
                    System.out.println();

                    Truck truck = truckController.createTruck();

                    System.out.println();

                    truckController.printTruckInfo(truck);

                    if (!coffeeController.isPricesSet() || input.getBoolean(
                            "Do you want to update the prices " + PrintColor.set("(true/false)", PrintColor.RED) + "?",
                            true)) {
                        coffeeController.updatePrices();
                    }

                    break;
                }
                case 'S': {
                    List<Truck> trucks = truckService.getTrucks();
                    int trucksSize = trucks.size();

                    if (trucksSize == 0) {
                        System.out.println();

                        ExceptionMessage.printCustom("You have not yet created any trucks!");

                        break;
                    }

                    Truck chosenTruck = null;

                    while (true) {
                        try {
                            System.out.println();

                            System.out.println("Which truck would you like to view?");

                            for (Truck truck : trucks) {
                                System.out.println("  [" + truck.id + "] Located at: "
                                        + PrintColor.set(truck.getLocation(), PrintColor.BRIGHT_CYAN));
                            }

                            System.out.println();
                            System.out.println("  [X] Return");

                            System.out.println();

                            System.out.print("  > ");

                            int chosenTruckId = scanner.nextInt();

                            scanner.nextLine();

                            if (chosenTruckId > 0 && chosenTruckId <= trucksSize) {
                                chosenTruck = truckService.getTruckById(chosenTruckId).get();

                                break;
                            } else {
                                System.out.println();

                                ExceptionMessage.INVALID_INTEGER_CHOICE.print();
                            }
                        } catch (InputMismatchException e) {
                            if (input.getCharacter() == 'X') {
                                break;
                            }

                            System.out.println();

                            ExceptionMessage.INVALID_INTEGER_CHOICE.print();
                        }
                    }

                    if (chosenTruck == null) {
                        break;
                    }

                    while (true) {
                        try {
                            System.out.println();

                            System.out.println("Which feature would you like to simulate?");
                            System.out.println("  [S] Sale and Preparation of the Coffee Drink");
                            System.out.println("  [V] View Truck Information");
                            System.out.println("  [R] Restocking of Storage Bins");
                            System.out.println("  [M] Maintenance");
                            System.out.println();
                            System.out.println("  [X] Return");

                            System.out.println();

                            System.out.print("  > ");

                            char chosenSubOptionId = input.getCharacter();

                            switch (chosenSubOptionId) {
                                case 'S':
                                    System.out.println();

                                    if (!coffeeController.isCapableOfBrewing(chosenTruck)) {
                                        ExceptionMessage.printCustom(
                                                "This coffee truck does not have the ingredients needed to brew coffee.");
                                    }

                                    coffeeController.prepareCoffee(chosenTruck);

                                    break;
                                case 'V':
                                    System.out.println();

                                    truckController.printTruckInfo(chosenTruck);

                                    if (coffeeController.isCapableOfBrewing(chosenTruck)) {
                                        System.out.println();

                                        coffeeController.printPrices(chosenTruck);
                                    }

                                    if (transactionController.hasTransactions(chosenTruck)) {
                                        System.out.println();

                                        transactionController.printTransactions(chosenTruck);
                                    }

                                    break;
                                case 'R':
                                    System.out.println();

                                    truckController.updateStorageBins(chosenTruck);

                                    break;
                                case 'M': {
                                    boolean isRelocating = input
                                            .getBoolean(
                                                    "Do you want to relocate the truck (currently located at: "
                                                            + PrintColor.set(chosenTruck.getLocation(),
                                                                    PrintColor.BRIGHT_CYAN)
                                                            + ") " + PrintColor.set("(true/false)", PrintColor.RED)
                                                            + "?",
                                                    true);

                                    if (isRelocating) {
                                        truckController.relocateTruck(chosenTruck);
                                    }

                                    if (input.getBoolean("Do you want to update the prices (of all trucks) "
                                            + PrintColor.set("(true/false)", PrintColor.RED) + "?", isRelocating)) {
                                        System.out.println();

                                        coffeeController.updatePrices();
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

                    break;
                }
                case 'D':
                    System.out.println();

                    truckController.printTrucksInfo();

                    System.out.println();

                    transactionController.printTransactions();

                    break;
                case 'X':
                    isExiting = true;

                    break;
                default:
                    System.out.println();

                    ExceptionMessage.INVALID_CHARACTER_CHOICE.print();

                    break;
            }

            if (!isExiting) {
                System.out.println();
            }
        }
    }
}
