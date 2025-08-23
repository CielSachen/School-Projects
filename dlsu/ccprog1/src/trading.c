/*
 * Tides of Manila is a turn-based trading game set in Manila.
 * Copyright (C) 2024  Raphael Panaligan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "trading.h"

#include <stdlib.h>

/**
 * @brief Generates a random price within the passed minimum and maximum prices.
 * @param nMinimumPrice The minimum allowed price.
 * @param nMaximumPrice The maximum allowed price.
 * @return An integer value within the range of `nMinimumPrice` and `nMaximumPrice`.
 */
int generateRandomPrice(int nMinimumPrice, int nMaximumPrice) {
  return (rand() % (nMaximumPrice - nMinimumPrice + 1)) + nMinimumPrice;
}

/**
 * @brief Subtracts or adds the cargo's cost to the player's balance and cargo to the ship's storage based on the
 * transaction type and prints out the game's transaction screen.
 * @param cTransactionTypeId The ID of the type of transaction made.
 * @param[out] nPlayerBalance The player's gold coin balance.
 * @param nCargoPrice The price of the cargo.
 * @param nCargoAmount The amount of cargo to trade.
 * @param[out] nShipCargoAmount The amount of cargo carried by the ship.
 * @pre @p cTransactionTypeId must have a character value of either `B` or `S`.
 */
void tradeCargo(char cTransactionTypeId, int* nPlayerBalance, int nCargoPrice, int nCargoAmount,
                int* nShipCargoAmount) {
  if (cTransactionTypeId == BUY_TRANSACTION_TYPE_ID) {
    *nPlayerBalance -= (nCargoPrice * nCargoAmount);
    *nShipCargoAmount += nCargoAmount;
  } else {
    *nPlayerBalance += (nCargoPrice * nCargoAmount);
    *nShipCargoAmount -= nCargoAmount;
  }
}

/**
 * @brief Subtracts the ship upgrade cost from the player's balance, sets the upgraded ship cargo limit, and prints out
 * the game's ship upgrade screen to the console.
 * @param[out] nPlayerBalance The player's gold coin balance.
 * @param nShipUpgradeCost The price of upgrading the ship.
 * @param[out] nShipCurrentCargoLimit The current maximum amount of cargo that the ship can carry.
 * @param nShipNewCargoLimit The upgraded maximum amount of cargo that the ship can carry.
 */
void upgradeShip(int* nPlayerBalance, int nShipUpgradeCost, int* nShipCurrentCargoLimit, int nShipNewCargoLimit) {
  *nPlayerBalance -= nShipUpgradeCost;
  *nShipCurrentCargoLimit = nShipNewCargoLimit;
}
