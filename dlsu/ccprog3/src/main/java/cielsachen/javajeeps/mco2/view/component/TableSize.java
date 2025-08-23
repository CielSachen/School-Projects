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

package cielsachen.javajeeps.mco2.view.component;

import java.awt.Dimension;

/** Represents the size of a table in pixels. */
public enum TableSize {
    /** A small table. */
    SMALL(220, 120),
    /** A medium table. */
    MEDIUM(330, 160),
    /** A large table. */
    LARGE(440, 200);

    /** The width of the table. */
    public final int width;
    /** The height of the table. */
    public final int height;
    /** The dimension of the table. */
    public final Dimension dimension;

    private TableSize(int width, int height) {
        this.width = width;
        this.height = height;
        dimension = new Dimension(width, height);
    }
}
