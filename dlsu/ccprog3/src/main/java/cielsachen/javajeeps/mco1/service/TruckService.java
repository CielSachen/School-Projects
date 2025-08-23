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

import cielsachen.javajeeps.mco1.model.Truck;

/**
 * Represents a service for managing trucks. The business logic happens here instead of in the models.
 * <p>
 * This uses a standard Java {@link List list} instead of a dedicated repository.
 */
public class TruckService {
    private final List<Truck> trucks;

    /**
     * Creates and returns a new {@code TruckService} object instance.
     *
     * @param trucks The list of trucks to use.
     */
    public TruckService(List<Truck> trucks) {
        this.trucks = trucks;
    }

    /**
     * Gets all trucks.
     *
     * @return An immutable list of all trucks.
     */
    public List<Truck> getTrucks() {
        return Collections.unmodifiableList(trucks);
    }

    /**
     * Gets the special trucks.
     *
     * @return An immutable list of special trucks.
     */
    public List<Truck> getSpecialTrucks() {
        return trucks.stream().filter((t) -> t.isSpecial).toList();
    }

    /**
     * Gets a truck with a specific ID.
     *
     * @param id The ID of the truck to get.
     * @return The truck with the specific ID.
     */
    public Optional<Truck> getTruckById(int id) {
        for (Truck truck : this.trucks) {
            if (truck.id == id) {
                return Optional.of(truck);
            }
        }

        return Optional.empty();
    }

    /**
     * Adds a truck to the list. If the truck's location is already occupied by an existing truck, the truck will not be
     * added.
     *
     * @param truck The truck to add.
     * @return Whether the truck was added to the list.
     */
    public boolean addTruck(Truck truck) {
        if (isOccupiedLocation(truck.getLocation())) {
            return false;
        }

        trucks.add(truck);

        return true;
    }

    /**
     * Checks whether a location is occupied by another truck.
     *
     * @param loc The location to check.
     * @return Whether the location is occupied by another truck.
     */
    public boolean isOccupiedLocation(String loc) {
        return trucks.stream().anyMatch((t) -> t.getLocation().equals(loc));
    }
}
