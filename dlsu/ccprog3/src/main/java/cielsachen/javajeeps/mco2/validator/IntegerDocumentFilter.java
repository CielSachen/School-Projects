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

package cielsachen.javajeeps.mco2.validator;

import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DocumentFilter;

/** Represents the filter used for preventing non-integers from being inputted in a text field. */
public class IntegerDocumentFilter extends DocumentFilter {
    /** Creates and returns a new {@code IntegerDocumentFilter} object instance. */
    public IntegerDocumentFilter() {
        super();
    }

    private boolean isInteger(String str) {
        if (str.isEmpty()) {
            return true;
        }

        try {
            Integer.parseInt(str);

            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    /** {@inheritDoc} */
    @Override
    public void insertString(FilterBypass filterBypass, int offset, String str, AttributeSet attrSet)
            throws BadLocationException {
        if (isInteger(str)) {
            super.insertString(filterBypass, offset, str, attrSet);
        }
    }

    /** {@inheritDoc} */
    @Override
    public void replace(FilterBypass filterBypass, int offset, int len, String text, AttributeSet attrSet)
            throws BadLocationException {
        if (isInteger(text)) {
            super.replace(filterBypass, offset, len, text, attrSet);
        }
    }
}
