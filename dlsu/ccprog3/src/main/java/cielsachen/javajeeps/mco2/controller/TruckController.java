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
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.swing.JComboBox;
import javax.swing.JOptionPane;

import cielsachen.javajeeps.mco2.model.Ingredient;
import cielsachen.javajeeps.mco2.model.StorageBin;
import cielsachen.javajeeps.mco2.model.Truck;
import cielsachen.javajeeps.mco2.service.CoffeeService;
import cielsachen.javajeeps.mco2.service.StorageBinService;
import cielsachen.javajeeps.mco2.service.TruckService;
import cielsachen.javajeeps.mco2.view.StorageBinRestockingMenuView;
import cielsachen.javajeeps.mco2.view.TruckView;
import cielsachen.javajeeps.mco2.view.component.Modal;
import cielsachen.javajeeps.mco2.view.form.IngredientSelectionForm;
import cielsachen.javajeeps.mco2.view.form.StorageBinAssignmentForm;
import cielsachen.javajeeps.mco2.view.form.TruckCreationForm;

/** Represents a controller for handling trucks. */
public class TruckController {
    private final CoffeeController coffeeController;

    private final TruckService service;
    private final StorageBinService storageBinService;
    private final CoffeeService coffeeService;

    /**
     * Creates and returns a new {@code TruckController} object instance.
     *
     * @param coffeeController  The coffee controller to use.
     * @param service           The truck service to use.
     * @param storageBinService The storage bin service to use.
     * @param coffeeService     The coffee service to use.
     */
    public TruckController(CoffeeController coffeeController, TruckService service, StorageBinService storageBinService,
            CoffeeService coffeeService) {
        this.coffeeController = coffeeController;

        this.service = service;
        this.storageBinService = storageBinService;
        this.coffeeService = coffeeService;
    }

    /**
     * Creates a new truck and adds it to the system.
     *
     * @param parentComp The parent component of the windows to be shown.
     */
    public void createTruck(Component parentComp) {
        var creationForm = new TruckCreationForm(parentComp);

        creationForm.submitButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                String givenLoc = creationForm.locationField.getText();

                if (givenLoc.isEmpty()) {
                    Modal.showErrorDialog(parentComp, "A location must be specified!", "Missing Field");

                    return;
                } else if (service.isOccupiedLocation(givenLoc)) {
                    Modal.showErrorDialog(parentComp, "A truck already exists on this location!", "Invalid Input");

                    return;
                }

                Truck truck = new Truck(service.getTrucks().size() + 1, givenLoc,
                        creationForm.isSpecialCheckBox.isSelected());

                service.addTruck(truck);

                var storageBinAssignmentForm = new StorageBinAssignmentForm(creationForm, truck);

                storageBinAssignmentForm.submitButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent evt) {
                        for (int i = 0; i < storageBinAssignmentForm.ingredientComboBoxes.size(); i++) {
                            JComboBox<Ingredient> ingredientComboBox = storageBinAssignmentForm.ingredientComboBoxes
                                    .get(i);

                            storageBinService.addStorageBin(
                                    new StorageBin(i + 1, truck, (Ingredient) ingredientComboBox.getSelectedItem()));
                        }

                        boolean isFirstTruck = !coffeeService.isPricesSet();

                        if (isFirstTruck || Modal.showConfirmDialog(parentComp, "Do you want to update the prices?",
                                "Update Prices") == JOptionPane.YES_OPTION) {
                            coffeeController.updatePrices(storageBinAssignmentForm);
                        }

                        new TruckView(parentComp, truck, storageBinService.getStorageBinsByTruck(truck),
                                isFirstTruck ? null : coffeeService.getCoffeesByTruck(truck),
                                isFirstTruck ? null : coffeeService.espresso,
                                isFirstTruck ? null : coffeeService.syrup);
                    }
                });
            }
        });
    }

    /**
     * Moves a truck to a new unoccupied location.
     *
     * @param parentComp The parent component of the windows to be shown.
     * @param truck      The truck to move.
     */
    public void relocateTruck(Component parentComp, Truck truck) {
        String givenLoc;

        while (true) {
            givenLoc = Modal.showInputDialog(parentComp, "Where will this truck be relocated to?", "Truck Relocation");

            System.out.println();

            if (givenLoc == null) {
                return;
            } else if (!service.isOccupiedLocation(givenLoc)) {
                break;
            }

            Modal.showErrorDialog(parentComp, "A truck already exists on this location!", "Truck Relocation");
        }

        truck.setLocation(givenLoc);

        JOptionPane.showMessageDialog(parentComp, "Relocated the coffee truck to " + givenLoc + "!", "Truck Relocation",
                JOptionPane.PLAIN_MESSAGE);
    }

    /**
     * Restocks, empties, or changes the ingredient of a truck's storage bin.
     *
     * @param parentComp The parent component of the windows to be shown.
     * @param truck      The truck to update a storage bin of.
     */
    public void updateStorageBins(Component parentComp, Truck truck) {
        List<StorageBin> storageBins = new ArrayList<>(storageBinService.getStorageBinsByTruck(truck));

        StorageBin selectedStorageBin = Modal.showSelectionDialog(parentComp, "Please select the storage bin to update",
                "Storage Bin Selection", storageBins, storageBins.getFirst());

        if (selectedStorageBin == null) {
            return;
        }

        var storageBinRestockingForm = new StorageBinRestockingMenuView(parentComp);

        storageBinRestockingForm.restockButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                Ingredient currIngredient = selectedStorageBin.getIngredient();
                double currCapacity = selectedStorageBin.getCapacity();

                if (currCapacity == currIngredient.maxCapacity) {
                    Modal.showErrorDialog(storageBinRestockingForm, "The storage bin is already full!",
                            "Storage Bin Restocking");

                    return;
                }

                double additionalCapacity = 0;

                while (true) {
                    String givenAmount = Modal.showInputDialog(parentComp,
                            "How much (" + currIngredient.unitMeasure + ") " + currIngredient + " should be restocked?",
                            "Storage Bin Restocking");

                    if (givenAmount == null) {
                        return;
                    }

                    try {
                        additionalCapacity = Double.parseDouble(givenAmount);

                        break;
                    } catch (NumberFormatException e) {
                        Modal.showErrorDialog(parentComp, "Please only input a floating point number!",
                                "Invalid Input");
                    }
                }

                if (additionalCapacity > 0) {
                    if (currCapacity + additionalCapacity > currIngredient.maxCapacity) {
                        selectedStorageBin.decreaseCapacity(currCapacity);
                        selectedStorageBin.increaseCapacity(currIngredient.maxCapacity);
                    } else {
                        selectedStorageBin.increaseCapacity(additionalCapacity);
                    }

                    JOptionPane.showMessageDialog(storageBinRestockingForm, "The storage bin has been restocked!",
                            "Storage Bin Restocking", JOptionPane.PLAIN_MESSAGE);
                }
            }
        });
        storageBinRestockingForm.emptyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                double currCapacity = selectedStorageBin.getCapacity();

                if (currCapacity == 0) {
                    Modal.showErrorDialog(storageBinRestockingForm, "The storage bin is already empty!",
                            "Storage Bin Restocking");

                    return;
                }

                selectedStorageBin.decreaseCapacity(currCapacity);

                JOptionPane.showMessageDialog(storageBinRestockingForm, "The storage bin has been emptied!",
                        "Storage Bin Restocking", JOptionPane.PLAIN_MESSAGE);
            }
        });
        storageBinRestockingForm.changeIngredientButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent evt) {
                List<Ingredient> ingredients = new ArrayList<>(
                        Arrays.asList(selectedStorageBin.id > StorageBin.STANDARD_TRUCK_COUNT
                                ? Ingredient.specialValues()
                                : Ingredient.regularValues()));

                storageBins.remove(selectedStorageBin);
                ingredients.remove(selectedStorageBin.getIngredient());

                var ingredientSelForm = new IngredientSelectionForm(parentComp, storageBins, ingredients);

                ingredientSelForm.submitButton.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent evt) {
                        double currCapacity = selectedStorageBin.getCapacity();

                        if (currCapacity > 0) {
                            selectedStorageBin.decreaseCapacity(currCapacity);
                        }

                        var selectedIngredient = (Ingredient) ingredientSelForm.ingredientComboBox.getSelectedItem();

                        selectedStorageBin.setIngredient(selectedIngredient);
                        selectedStorageBin.increaseCapacity(selectedIngredient.maxCapacity);
                    }
                });
            }
        });
    }
}
