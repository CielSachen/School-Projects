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

#ifndef TRADING_H_
#define TRADING_H_

#define TONDO_MINIMUM_COCONUT_PRICE 4
#define TONDO_MAXIMUM_COCONUT_PRICE 24
#define TONDO_MINIMUM_RICE_PRICE 1
#define TONDO_MAXIMUM_RICE_PRICE 20
#define TONDO_MINIMUM_SILK_PRICE 48
#define TONDO_MAXIMUM_SILK_PRICE 68
#define TONDO_MINIMUM_GUN_PRICE 70
#define TONDO_MAXIMUM_GUN_PRICE 95

#define MANILA_MINIMUM_COCONUT_PRICE 3
#define MANILA_MAXIMUM_COCONUT_PRICE 18
#define MANILA_MINIMUM_RICE_PRICE 5
#define MANILA_MAXIMUM_RICE_PRICE 20
#define MANILA_MINIMUM_SILK_PRICE 24
#define MANILA_MAXIMUM_SILK_PRICE 39
#define MANILA_MINIMUM_GUN_PRICE 65
#define MANILA_MAXIMUM_GUN_PRICE 84

#define PANDAKAN_MINIMUM_COCONUT_PRICE 2
#define PANDAKAN_MAXIMUM_COCONUT_PRICE 12
#define PANDAKAN_MINIMUM_RICE_PRICE 4
#define PANDAKAN_MAXIMUM_RICE_PRICE 14
#define PANDAKAN_MINIMUM_SILK_PRICE 22
#define PANDAKAN_MAXIMUM_SILK_PRICE 32
#define PANDAKAN_MINIMUM_GUN_PRICE 90
#define PANDAKAN_MAXIMUM_GUN_PRICE 103

#define SAPA_MINIMUM_COCONUT_PRICE 9
#define SAPA_MAXIMUM_COCONUT_PRICE 14
#define SAPA_MINIMUM_RICE_PRICE 1
#define SAPA_MAXIMUM_RICE_PRICE 6
#define SAPA_MINIMUM_SILK_PRICE 17
#define SAPA_MAXIMUM_SILK_PRICE 22
#define SAPA_MINIMUM_GUN_PRICE 204
#define SAPA_MAXIMUM_GUN_PRICE 301

#define BUY_TRANSACTION_TYPE_ID 'B'
#define SELL_TRANSACTION_TYPE_ID 'S'

#define TIER_ONE_SHIP_CARGO_LIMIT 75
#define TIER_TWO_SHIP_CARGO_LIMIT 150
#define TIER_THREE_SHIP_CARGO_LIMIT 225
#define TIER_FOUR_SHIP_CARGO_LIMIT 300

#define TIER_TWO_SHIP_UPGRADE_COST 1000
#define TIER_THREE_SHIP_UPGRADE_COST 1750
#define TIER_FOUR_SHIP_UPGRADE_COST 2500

/**
 * @brief Generates a random price within the passed minimum and maximum prices.
 * @param nMinimumPrice The minimum allowed price.
 * @param nMaximumPrice The maximum allowed price.
 * @return An integer value within the range of `nMinimumPrice` and `nMaximumPrice`.
 */
int generateRandomPrice(int nMinimumPrice, int nMaximumPrice);

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
void tradeCargo(char cTransactionTypeId, int* nPlayerBalance, int nCargoPrice, int nCargoAmount, int* nShipCargoAmount);

/**
 * @brief Subtracts the ship upgrade cost from the player's balance, sets the upgraded ship cargo limit, and prints out
 * the game's ship upgrade screen to the console.
 * @param[out] nPlayerBalance The player's gold coin balance.
 * @param nShipUpgradeCost The price of upgrading the ship.
 * @param[out] nShipCurrentCargoLimit The current maximum amount of cargo that the ship can carry.
 * @param nShipNewCargoLimit The upgraded maximum amount of cargo that the ship can carry.
 */
void upgradeShip(int* nPlayerBalance, int nShipUpgradeCost, int* nShipCurrentCargoLimit, int nShipNewCargoLimit);

#endif  // TRADING_H_
