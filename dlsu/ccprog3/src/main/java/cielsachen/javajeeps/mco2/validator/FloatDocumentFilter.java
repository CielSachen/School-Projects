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
import javax.swing.text.Document;
import javax.swing.text.DocumentFilter;

/** Represents the filter used for preventing non-floats from being inputted in a text field. */
public class FloatDocumentFilter extends DocumentFilter {
    /** Creates and returns a new {@code FloatDocumentFilter} object instance. */
    public FloatDocumentFilter() {
        super();
    }

    private boolean isFloat(String str) {
        if (str.isEmpty()) {
            return true;
        }

        try {
            Float.parseFloat(str);

            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }

    /** {@inheritDoc} */
    @Override
    public void insertString(FilterBypass filterBypass, int offset, String str, AttributeSet attrSet)
            throws BadLocationException {
        Document currDoc = filterBypass.getDocument();
        String currStr = currDoc.getText(0, currDoc.getLength());

        if (isFloat(currStr.substring(0, offset) + str + currStr.substring(offset))) {
            super.insertString(filterBypass, offset, str, attrSet);
        }
    }

    /** {@inheritDoc} */
    @Override
    public void replace(FilterBypass filterBypass, int offset, int len, String text, AttributeSet attrSet)
            throws BadLocationException {
        Document currDoc = filterBypass.getDocument();
        String currText = currDoc.getText(0, currDoc.getLength());

        if (isFloat(currText.substring(0, offset) + text + currText.substring(offset + len))) {
            super.replace(filterBypass, offset, len, text, attrSet);
        }
    }
}
