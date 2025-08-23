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

package cielsachen.javajeeps.mco1.service;

import java.util.Collections;
import java.util.List;
import java.util.Optional;

import cielsachen.javajeeps.mco1.model.Ingredient;
import cielsachen.javajeeps.mco1.model.StorageBin;
import cielsachen.javajeeps.mco1.model.Truck;

/**
 * Represents a service for managing storage bins. The business logic happens here instead of in the models.
 * <p>
 * This uses a standard Java {@link List list} instead of a dedicated repository.
 */
public class StorageBinService {
    private final List<StorageBin> storageBins;

    /**
     * Creates and returns a new {@code StorageBinService} object instance.
     *
     * @param storageBins The list of storage bins to use.
     */
    public StorageBinService(List<StorageBin> storageBins) {
        this.storageBins = storageBins;
    }

    /**
     * Gets all storage bins belonging to any trucks.
     *
     * @return An immutable list of all storage bins.
     */
    public List<StorageBin> getStorageBins() {
        return Collections.unmodifiableList(storageBins);
    }

    /**
     * Gets all storage bins containing an ingredient.
     *
     * @param ingredient The ingredient contained by the storage bins to get.
     * @return An immutable list of storage bins containing the ingredient.
     */
    public List<StorageBin> getStorageBinsByIngredient(Ingredient ingredient) {
        return storageBins.stream().filter((sb) -> sb.getIngredient().equals(ingredient)).toList();
    }

    /**
     * Gets all storage bins belonging to a truck.
     *
     * @param truck The truck owning the storage bins to get.
     * @return An immutable list of storage bins belonging to the truck.
     */
    public List<StorageBin> getStorageBinsByTruck(Truck truck) {
        return storageBins.stream().filter((sb) -> sb.truck.equals(truck)).toList();
    }

    /**
     * Gets all storage bins belonging to a truck and containing an ingredient.
     *
     * @param truck      The truck owning the storage bins to get.
     * @param ingredient The ingredient contained by the storage bins to get.
     * @return An immutable list of storage bins belonging to the truck and containing the ingredient.
     */
    public List<StorageBin> getStorageBinsByTruck(Truck truck, Ingredient ingredient) {
        return storageBins
                .stream()
                .filter((sb) -> sb.truck.equals(truck) && sb.getIngredient().equals(ingredient))
                .toList();
    }

    /**
     * Gets the storage bin with a specific ID belonging to a truck.
     *
     * @param id    The ID of the storage bin to get.
     * @param truck The truck owning the storage bin to get.
     * @return The storage bin with the specific ID belonging to the truck.
     */
    public Optional<StorageBin> getStorageBinById(int id, Truck truck) {
        for (StorageBin storageBin : this.getStorageBinsByTruck(truck)) {
            if (storageBin.id == id) {
                return Optional.of(storageBin);
            }
        }

        return Optional.empty();
    }

    /**
     * Adds a storage bin to the list.
     *
     * @param storageBin The storage bin to add.
     */
    public void addStorageBin(StorageBin storageBin) {
        storageBins.add(storageBin);
    }

    /**
     * Gets the total capacity of all storage bins belonging to a truck and containing an ingredient.
     *
     * @param truck      The truck owning the storage bins.
     * @param ingredient The ingredient contained by the storage bins to get.
     * @return The total capacity of the storage bins belonging to the truck and containing the ingredient.
     */
    public double getTotalCapacityByTruck(Truck truck, Ingredient ingredient) {
        return getStorageBinsByTruck(truck, ingredient).stream().mapToDouble((sb) -> sb.getCapacity()).sum();
    }

    /**
     * Decreases the capacities of storage bins belonging to a truck and containing an ingredient.
     * <p>
     * The storage bins are "overflowed", meaning that once a storage bin is empty, the next storage bin's capacity will
     * be decreased.
     *
     * @param truck      The truck owning the storage bins.
     * @param ingredient The ingredient contained by the storage bins.
     * @param amount     The amount to decrease the capacities by.
     * @return Whether the capacities of the storage bins was decreased.
     */
    public boolean decreaseCapacityByTruck(Truck truck, Ingredient ingredient, double amount) {
        if (getTotalCapacityByTruck(truck, ingredient) < amount) {
            return false;
        }

        double remainingAmount = amount;

        for (StorageBin storageBin : getStorageBinsByTruck(truck, ingredient)) {
            if (storageBin.getCapacity() >= remainingAmount) {
                storageBin.decreaseCapacity(remainingAmount);

                break;
            }

            remainingAmount -= storageBin.getCapacity();

            storageBin.decreaseCapacity(storageBin.getCapacity());
        }

        return true;
    }

    /**
     * Checks whether a truck has storage bins containing certain ingredients.
     *
     * @param truck       The truck to check.
     * @param ingredients The ingredients to check against.
     * @return Whether the truck has storage bins containing the ingredients.
     */
    public boolean truckHasIngredient(Truck truck, Ingredient... ingredients) {
        boolean hasIngredient = false;

        for (Ingredient ingredient : ingredients) {
            for (StorageBin storageBin : storageBins) {
                if (storageBin.getIngredient().equals(ingredient)) {
                    hasIngredient = true;

                    break;
                }
            }

            if (!hasIngredient) {
                return false;
            }
        }

        return true;
    }

    /**
     * Checks whether a truck has storage bins containing syrups.
     *
     * @param truck The truck to check.
     * @return Whether the truck has storage bins containing syrups.
     */
    public boolean truckHasSyrups(Truck truck) {
        return storageBins.stream().anyMatch((sb) -> sb.getIngredient().isSpecial);
    }
}
