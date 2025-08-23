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

package cielsachen.javajeeps.mco1;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import cielsachen.javajeeps.mco1.controller.CoffeeController;
import cielsachen.javajeeps.mco1.controller.MenuController;
import cielsachen.javajeeps.mco1.controller.TransactionController;
import cielsachen.javajeeps.mco1.controller.TruckController;
import cielsachen.javajeeps.mco1.helper.Input;
import cielsachen.javajeeps.mco1.model.StorageBin;
import cielsachen.javajeeps.mco1.model.Transaction;
import cielsachen.javajeeps.mco1.model.Truck;
import cielsachen.javajeeps.mco1.service.CoffeeService;
import cielsachen.javajeeps.mco1.service.StorageBinService;
import cielsachen.javajeeps.mco1.service.TransactionService;
import cielsachen.javajeeps.mco1.service.TruckService;

/** Represents the entry point for Java programs. */
public class Main {
    Main() {
    }

    /**
     * Executes the Java program.
     *
     * @param args The CLI arguments.
     */
    public static void main(String[] args) {
        var scanner = new Scanner(System.in);
        var input = new Input(scanner);

        List<Transaction> transactions = new ArrayList<Transaction>();
        List<StorageBin> storageBins = new ArrayList<StorageBin>();
        List<Truck> trucks = new ArrayList<Truck>();

        var transactionService = new TransactionService(transactions);
        var storageBinService = new StorageBinService(storageBins);
        var coffeeService = new CoffeeService(storageBinService);
        var truckService = new TruckService(trucks);

        var transactionController = new TransactionController(transactionService);
        var coffeeController = new CoffeeController(coffeeService, storageBinService, transactionService, scanner,
                input);
        var truckController = new TruckController(truckService, storageBinService, scanner, input);
        var menuController = new MenuController(truckController, coffeeController, transactionController, truckService,
                scanner, input);

        menuController.printMainMenu();
    }
}
