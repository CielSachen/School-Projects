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

package cielsachen.javajeeps.mco1.controller;

import java.util.List;
import java.util.Map;

import cielsachen.javajeeps.mco1.helper.PrintColor;
import cielsachen.javajeeps.mco1.model.Ingredient;
import cielsachen.javajeeps.mco1.model.Transaction;
import cielsachen.javajeeps.mco1.model.Truck;
import cielsachen.javajeeps.mco1.service.TransactionService;
import cielsachen.javajeeps.mco1.util.Output;

/** Represents a controller for interacting with transactions. */
public class TransactionController {
    private final TransactionService service;

    /**
     * Creates and returns a new {@code TransactionController} object instance.
     *
     * @param service The transaction service to use.
     */
    public TransactionController(TransactionService service) {
        this.service = service;
    }

    /**
     * Checks if a truck has any linked transactions. This wraps the {@link TransactionService#hasTransactions
     * hasTransactions()} method.
     *
     * @param truck The truck to check.
     * @return Whether the truck has any linked transactions.
     */
    public boolean hasTransactions(Truck truck) {
        return service.hasTransactions(truck);
    }

    /**
     * Prints all of the transactions linked with a truck.
     *
     * @param truck The truck to use.
     */
    public void printTransactions(Truck truck) {
        Output.printHeader3("Transactions");

        List<Transaction> transactions = service.getTransactionsByTruck(truck);

        for (int i = 0; i < transactions.size(); i++) {
            System.out.println();

            Transaction transaction = transactions.get(i);

            System.out.println("Transaction " + (i + 1));
            System.out.println("  Coffee: " + PrintColor.set(transaction.coffeeName, PrintColor.BRIGHT_CYAN));
            System.out.println("  Ingredients:");

            for (Map.Entry<Ingredient, Double> entry : transaction.getIngredients().entrySet()) {
                Ingredient ingredient = entry.getKey();

                System.out.println("    " + ingredient.name + ": " + PrintColor.set(
                        String.format("%.2f %s", entry.getValue(), ingredient.unitMeasure), PrintColor.BRIGHT_CYAN));
            }

            System.out.println("  Total Cost: " + PrintColor.set(transaction.toCostString(), PrintColor.BRIGHT_GREEN));
        }
    }

    /** Prints all transactions linked with all trucks. */
    public void printTransactions() {
        Output.printHeader3("Transactions");

        List<Transaction> transactions = service.getTransactions();

        for (int i = 0; i < transactions.size(); i++) {
            System.out.println();

            Transaction transaction = transactions.get(i);

            System.out.println("Transaction " + (i + 1));
            System.out.println(
                    "  Truck ID: " + PrintColor.set(Integer.toString(transaction.truck.id), PrintColor.BRIGHT_CYAN));
            System.out.println("  Coffee: " + PrintColor.set(transaction.coffeeName, PrintColor.BRIGHT_CYAN));
            System.out.println("  Ingredients:");

            for (Map.Entry<Ingredient, Double> entry : transaction.getIngredients().entrySet()) {
                Ingredient ingredient = entry.getKey();

                System.out.println("    " + ingredient.name + ": " + PrintColor.set(
                        String.format("%.2f %s", entry.getValue(), ingredient.unitMeasure), PrintColor.BRIGHT_CYAN));
            }

            System.out.println("  Total Cost: " + PrintColor.set(transaction.toCostString(), PrintColor.BRIGHT_GREEN));
        }
    }
}
