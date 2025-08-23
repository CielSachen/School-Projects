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

package cielsachen.javajeeps.mco2.model;

/** Represents a coffee truck. */
public class Truck {
    /** The one-based ID of the truck. */
    public final int id;
    /** Whether the truck is special. */
    public final boolean isSpecial;

    private String loc;

    /**
     * Creates and returns a new {@code Truck} object instance.
     *
     * @param id        The ID of the truck.
     * @param loc       The location of the truck.
     * @param isSpecial Whether the truck is special.
     */
    public Truck(int id, String loc, boolean isSpecial) {
        this.id = id;
        this.isSpecial = isSpecial;

        this.loc = loc;
    }

    /**
     * Gets the location of the truck.
     *
     * @return The location of the truck.
     */
    public String getLocation() {
        return loc;
    }

    /**
     * Sets the location of the truck.
     *
     * @param newLoc The new location to use.
     */
    public void setLocation(String newLoc) {
        loc = newLoc;
    }

    /**
     * Converts the truck into its string representation.
     *
     * @return The stylized location of the truck.
     */
    @Override
    public String toString() {
        return "Located at: " + getLocation();
    }
}
