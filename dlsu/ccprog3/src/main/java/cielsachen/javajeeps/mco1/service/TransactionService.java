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

import cielsachen.javajeeps.mco1.model.Transaction;
import cielsachen.javajeeps.mco1.model.Truck;

/**
 * Represents a service for managing transactions. The business logic happens here instead of in the models.
 * <p>
 * This uses a standard Java {@link List list} instead of a dedicated repository.
 */
public class TransactionService {
    private final List<Transaction> transactions;

    /**
     * Creates and returns a new {@code TransactionService} object instance.
     *
     * @param transactions The list of transactions to use.
     */
    public TransactionService(List<Transaction> transactions) {
        this.transactions = transactions;
    }

    /**
     * Gets all transactions linked with any trucks.
     *
     * @return An immutable list of all transactions.
     */
    public List<Transaction> getTransactions() {
        return Collections.unmodifiableList(transactions);
    }

    /**
     * Gets all transactions linked with a truck.
     *
     * @param truck The truck linked with the transactions to get.
     * @return An immutable list of transactions linked with the truck.
     */
    public List<Transaction> getTransactionsByTruck(Truck truck) {
        return transactions.stream().filter((t) -> t.truck.equals(truck)).toList();
    }

    /**
     * Adds a transaction to the list.
     *
     * @param transaction The transaction to add.
     */
    public void addTransaction(Transaction transaction) {
        transactions.add(transaction);
    }

    /**
     * Checks if a truck has any linked transactions.
     *
     * @param truck The truck to check.
     * @return Whether the truck has linked transactions.
     */
    public boolean hasTransactions(Truck truck) {
        return this.getTransactionsByTruck(truck).size() > 0;
    }
}
