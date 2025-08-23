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

package cielsachen.javajeeps.mco2;

import java.util.ArrayList;
import java.util.List;

import com.formdev.flatlaf.FlatLightLaf;

import cielsachen.javajeeps.mco2.controller.CoffeeController;
import cielsachen.javajeeps.mco2.controller.MenuController;
import cielsachen.javajeeps.mco2.controller.TruckController;
import cielsachen.javajeeps.mco2.model.StorageBin;
import cielsachen.javajeeps.mco2.model.Transaction;
import cielsachen.javajeeps.mco2.model.Truck;
import cielsachen.javajeeps.mco2.service.CoffeeService;
import cielsachen.javajeeps.mco2.service.StorageBinService;
import cielsachen.javajeeps.mco2.service.TransactionService;
import cielsachen.javajeeps.mco2.service.TruckService;

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
        List<Transaction> transactions = new ArrayList<>();
        List<StorageBin> storageBins = new ArrayList<>();
        List<Truck> trucks = new ArrayList<>();

        var transactionSvc = new TransactionService(transactions);
        var storageBinSvc = new StorageBinService(storageBins);
        var coffeeSvc = new CoffeeService(storageBinSvc);
        var truckSvc = new TruckService(trucks);

        FlatLightLaf.setup();

        var coffeeController = new CoffeeController(coffeeSvc, storageBinSvc, transactionSvc);
        var truckController = new TruckController(coffeeController, truckSvc, storageBinSvc, coffeeSvc);
        var menuController = new MenuController(truckController, coffeeController, truckSvc, storageBinSvc, coffeeSvc,
                transactionSvc);

        menuController.showMainMenu();
    }
}
