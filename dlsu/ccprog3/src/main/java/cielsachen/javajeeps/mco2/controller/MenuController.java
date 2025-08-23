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

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

import javax.swing.JOptionPane;

import cielsachen.javajeeps.mco2.model.Truck;
import cielsachen.javajeeps.mco2.service.CoffeeService;
import cielsachen.javajeeps.mco2.service.StorageBinService;
import cielsachen.javajeeps.mco2.service.TransactionService;
import cielsachen.javajeeps.mco2.service.TruckService;
import cielsachen.javajeeps.mco2.view.DashboardView;
import cielsachen.javajeeps.mco2.view.MainMenuView;
import cielsachen.javajeeps.mco2.view.SimulationMenuView;
import cielsachen.javajeeps.mco2.view.TruckView;
import cielsachen.javajeeps.mco2.view.component.Modal;

/** Represents a controller for handling the main menus. */
public class MenuController {
    private final MainMenuView view = new MainMenuView();

    /**
     * Creates and returns a new {@code MenuController} object instance.
     *
     * @param truckController    The truck controller to use.
     * @param coffeeController   The coffee controller to use.
     * @param truckService       The truck service to use.
     * @param storageBinService  The storage bin service to use.
     * @param coffeeService      The coffee service to use.
     * @param transactionService The transaction service to use.
     */
    public MenuController(TruckController truckController, CoffeeController coffeeController, TruckService truckService,
            StorageBinService storageBinService, CoffeeService coffeeService, TransactionService transactionService) {
        view.createTruckButton.addActionListener((e) -> truckController.createTruck(view));
        view.simulateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                List<Truck> trucks = truckService.getTrucks();

                if (trucks.size() == 0) {
                    Modal.showErrorDialog(view, "You have not yet created any trucks!", "Truck Selection");

                    return;
                }

                Truck selectedTruck = Modal.showSelectionDialog(view, "Please select a truck by its location…",
                        "Truck Selection", trucks, trucks.getFirst());

                if (selectedTruck == null) {
                    return;
                }

                var simulationForm = new SimulationMenuView(view);

                simulationForm.coffeeSaleButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent evt) {
                        if (!coffeeService.isCapableOfBrewing(selectedTruck)) {
                            Modal.showErrorDialog(simulationForm,
                                    "The selected truck doesn't have the ingredients to brew coffee!",
                                    "Missing Ingredients");

                            return;
                        }

                        coffeeController.prepareCoffee(simulationForm, selectedTruck);
                    }
                });
                simulationForm.viewTruckButton.addActionListener((e) -> new TruckView(simulationForm, selectedTruck,
                        storageBinService.getStorageBinsByTruck(selectedTruck),
                        coffeeService.getCoffeesByTruck(selectedTruck), coffeeService.espresso,
                        coffeeService.syrup, transactionService.getTransactionsByTruck(selectedTruck)));
                simulationForm.restockButton
                        .addActionListener((e) -> truckController.updateStorageBins(simulationForm, selectedTruck));
                simulationForm.maintenanceButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent evt) {
                        if (Modal.showConfirmDialog(simulationForm,
                                "Do you want to relocate the truck (currently located at: "
                                        + selectedTruck.getLocation() + ")?",
                                "Truck Relocation") == JOptionPane.YES_OPTION) {
                            truckController.relocateTruck(simulationForm, selectedTruck);
                        }

                        if (Modal.showConfirmDialog(simulationForm,
                                "Do you want to update the coffee prices (of all trucks)?",
                                "Coffee Prices Configuration") == JOptionPane.YES_OPTION) {
                            coffeeController.updatePrices(simulationForm);
                        }
                    }
                });
            }
        });
        view.dashboardButton.addActionListener((e) -> new DashboardView(view, truckService.getTrucks().size(),
                truckService.getSpecialTrucks().size(), storageBinService.getIngredientCapacities(),
                transactionService.getTransactions()));
    }

    /** Shows the main menu application GUI. */
    public void showMainMenu() {
        view.setVisible(true);
    }
}
