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

#ifndef TEXT_GRAPHICS_H_
#define TEXT_GRAPHICS_H_

/** @brief Prints out a pre-formatted separator line to the console. */
void printSeparator(void);

/** @brief Prints out the game's start screen, which contains the game's title, to the console. */
void printGameStartScreen(void);

/**
 * @brief Prints out the ship's sprite based on the passed cargo limit.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 */
void printShipSprite(int nShipCargoLimit);

/**
 * @brief Prints out the game's main menu screen, which contains statistics about the player and their ship and the
 * port's cargo market prices, to the console.
 * @param nPlayerTurns The number of turns the player has exhausted.
 * @param cPortId The ID of the port.
 * @param nPlayerId The player's merchant ID.
 * @param nPlayerBalance The player's gold coin balance.
 * @param nPlayerProfit The player's profit percentage.
 * @param nPlayerProfitTarget The player's target profit percentage.
 * @param nShipTotalCargoAmount The total amount of cargo carried by the ship.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 * @param nShipCoconutCargoAmount The amount of coconut cargo carried by the ship.
 * @param nShipRiceCargoAmount The amount of rice cargo carried by the ship.
 * @param nShipSilkCargoAmount The amount of silk cargo carried by the ship.
 * @param nShipGunCargoAmount The amount of gun cargo carried by the ship.
 * @param nCoconutMarketPrice The market price of coconuts.
 * @param nRiceMarketPrice The market price of rice.
 * @param nSilkMarketPrice The market price of silk.
 * @param nGunMarketPrice The market price of guns.
 * @pre @p nPlayerTurns must have a positive integer value less than or equal to `29`.
 * @pre @p cPortId must have a character value of `T`, `M`, `P`, or `S`.
 */
void printMainScreen(int nPlayerTurns, char cPortId, int nPlayerId, int nPlayerBalance, int nPlayerProfit,
                     int nPlayerProfitTarget, int nShipTotalCargoAmount, int nShipCargoLimit,
                     int nShipCoconutCargoAmount, int nShipRiceCargoAmount, int nShipSilkCargoAmount,
                     int nShipGunCargoAmount, int nCoconutMarketPrice, int nRiceMarketPrice, int nSilkMarketPrice,
                     int nGunMarketPrice);

/**
 * @brief Prints out the game's transaction screen, which contains the name of the cargo that the player traded and the
 * number of gold coins the player has spent or earned, to the console.
 * @param cTransactionType The type of transaction made.
 * @param cCargoId The ID of the traded cargo.
 * @param nCargoAmount The amount of cargo to trade.
 * @param nCargoPrice The price of the cargo.
 * @pre @p cTransactionType must have a character value of either `B` or `S`.
 * @pre @p cCargoId must have a character value of `C`, `R`, `S`, or `G`.
 */
void printTransactionScreen(char cTransactionType, char cCargoId, int nCargoAmount, int nCargoPrice);

/**
 * @brief Prints out the game's ship upgrade menu, which contains a preview of the upgraded ship and details about its
 * cargo capacity and price, to the console.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 */
void printShipUpgradeMenu(int nShipCargoLimit);

/**
 * @brief Prints out the game's ship upgrade screen, which contains the number of additional cargo spaces the ship has
 * received and gold coins the player has spent, to the console.
 * @param nShipCargoLimitIncrease The amount of additional cargo space the ship has gotten.
 * @param nShipUpgradeCost The price of the ship upgrade.
 */
void printShipUpgradeScreen(int nShipCargoLimitIncrease, int nShipUpgradeCost);

/**
 * @brief Prints out the game's navigation screen, which contains the new port the player navigated to and the new day
 * count, to the console.
 * @param bIsSuccessful Whether or not the departure was successful.
 * @param cPortId The ID of the port.
 * @param nPlayerTurns The number of turns the player has exhausted.
 * @pre @p bIsSuccessful must have an integer value of either `0` or `1`.
 * @pre @p cPortId must have a character value of `T`, `M`, `P`, or `S`.
 * @pre @p nPlayerTurns must have a a two-digit positive integer value.
 */
void printNavigationMenu(char cCurrentPortId, int nPlayerTurns);

/**
 * @brief Prints out the game's navigation screen, which contains the new port the player navigated to and the new day
 * count, to the console.
 * @param cPortId The ID of the port.
 * @param nPlayerTurns The number of turns the player has exhausted.
 * @pre @p cPortId must have a character value of `T`, `M`, `P`, or `S`.
 * @pre @p nPlayerTurns must have a a two-digit positive integer value.
 */
void printNavigationScreen(int bIsSuccessful, char cPortId, int nPlayerTurns);

/**
 * @brief Prints out the game's weather report screen, which contains details about the storm and the applied debuffs,
 * to the console.
 * @param bIsNewStorm Whether or not the storm is new.
 * @param nStormOldWindSignalNumber The storm's old wind signal number.
 * @param nStormNewWindSignalNumber The storm's new wind signal number.
 * @param nPostponedDepartureChance The percentage chance of the player being unable to depart their current port.
 * @param nStormTurnDuration The turn duration of the storm.
 * @pre @p bIsNewStorm must have an integer value of either `0` or `1`.
 */
void printWeatherReportScreen(int bIsNewStorm, int nStormOldWindSignalNumber, int nStormNewWindSignalNumber,
                              int nPostponedDepartureChance, int nStormTurnDuration);

/**
 * @brief Prints out the game's end screen, which contains the player's final statistics, to the console.
 * @param nPlayerFinalProfit The player's final profit percentage.
 * @param nPlayerProfitTarget The player's target profit percentage.
 * @param nPlayerFinalBalance The player's final gold coin balance.
 * @param nPlayerInitialBalance The player's inital gold coin balance.
 * @param nPlayerFinalTurns The number of turns the player has exhausted.
 */
void printGameEndScreen(int nPlayerFinalProfit, int nPlayerProfitTarget, int nPlayerFinalBalance,
                        int nPlayerInitialBalance, int nPlayerFinalTurns);

#endif  // TEXT_GRAPHICS_H_
