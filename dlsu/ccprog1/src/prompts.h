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

#ifndef PROMPTS_H_
#define PROMPTS_H_

#define MINIMUM_MERCHANT_ID_VALUE 0
#define MAXIMUM_MERCHANT_ID_VALUE 999

#define MINIMUM_INITIAL_BALANCE 1

#define MINIMUM_TARGET_PROFIT 20

#define YES_ID 'Y'
#define NO_ID 'N'

#define BUY_ACTION_ID 'B'
#define SELL_ACTION_ID 'S'
#define UPGRADE_ACTION_ID 'U'
#define NAVIGATE_ACTION_ID 'N'
#define QUIT_ACTION_ID 'Q'
#define CANCEL_ACTION_ID 'X'

#define COCONUT_CARGO_ID 'C'
#define RICE_CARGO_ID 'R'
#define SILK_CARGO_ID 'S'
#define GUN_CARGO_ID 'G'

#define TONDO_PORT_ID 'T'
#define MANILA_PORT_ID 'M'
#define PANDAKAN_PORT_ID 'P'
#define SAPA_PORT_ID 'S'

/**
 * @brief Prompts the player to input their preferred merchant ID.
 * @return An integer value within the range of `0` and `999`.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForMerchantId(void);

/**
 * @brief Prompts the player to input the number of gold coins they want to start with.
 * @return An integer value greater than `0`.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForInitialBalance(void);

/**
 * @brief Prompts the player to input their desired profit target.
 * @return An integer value greater than `20`.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForProfitTarget(void);

/**
 * @brief Prompts the player to input a confirmation of their prior decision.
 * @return `1` if the player confirms or `0` if they do not.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForConfirmation(void);

/** Prompts the player to press the enter or return key to continue the game. */
void promptPlayerForContinuation(void);

/**
 * @brief Prompts the player to input the ID of the action they want to do.
 * @param nShipTotalCargoAmount The total amount of cargo carried by the ship.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 * @param nPlayerBalance The player's gold coin balance.
 * @param nCoconutMarketPrice The market price of coconuts.
 * @param nRiceMarketPrice The market price of rice.
 * @param nSilkMarketPrice The market price of silk.
 * @param nGunMarketPrice The market price of guns.
 * @return A character value of `B` for the buy screen, `S` for the sell screen, `U` for the ship
 * upgrade screen, `N` for the navigation screen, or `Q` for quitting the game.
 */
char promptPlayerForActionId(int nShipTotalCargoAmount, int nShipCargoLimit, int nPlayerBalance,
                             int nCoconutMarketPrice, int nRiceMarketPrice, int nSilkMarketPrice, int nGunMarketPrice);

/**
 * @brief Prompts the player to input the ID of the cargo they want to trade.
 * @param cTransactionTypeId The ID of the type of transaction to make.
 * @param nPlayerBalance The player's gold coin balance.
 * @param nCoconutMarketPrice The market price of coconuts.
 * @param nRiceMarketPrice The market price of rice.
 * @param nSilkMarketPrice The market price of silk.
 * @param nGunMarketPrice The market price of guns.
 * @param nShipCoconutCargoAmount The amount of coconut cargo carried by the ship.
 * @param nShipRiceCargoAmount The amount of rice cargo carried by the ship.
 * @param nShipSilkCargoAmount The amount of silk cargo carried by the ship.
 * @param nShipGunCargoAmount The amount of gun cargo carried by the ship.
 * @pre @p cTransactionTypeId must have a character value of either `B` or `S`.
 * @return A character value of `C` for coconut, `R` for rice, `S` for silk, `G` for gun, or `X`
 * for returning to the main menu.
 */
char promptPlayerForCargoId(char cTransactionTypeId, int nPlayerBalance, int nCoconutMarketPrice, int nRiceMarketPrice,
                            int nSilkMarketPrice, int nGunMarketPrice, int nShipCoconutCargoAmount,
                            int nShipRiceCargoAmount, int nShipSilkCargoAmount, int nShipGunCargoAmount);

/**
 * @brief Prompts the player to input the amount of cargo they want to trade.
 * @param cTransactionTypeId The ID of the type of transaction to make.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 * @param cCargoId The ID of the traded cargo.
 * @param nPlayerBalance The player's gold coin balance.
 * @param nCoconutMarketPrice The market price of coconuts.
 * @param nRiceMarketPrice The market price of rice.
 * @param nSilkMarketPrice The market price of silk.
 * @param nGunMarketPrice The market price of guns.
 * @param nShipCoconutCargoAmount The amount of coconut cargo carried by the ship.
 * @param nShipRiceCargoAmount The amount of rice cargo carried by the ship.
 * @param nShipSilkCargoAmount The amount of silk cargo carried by the ship.
 * @param nShipGunCargoAmount The amount of gun cargo carried by the ship.
 * @pre @p cTransactionTypeId must have a character value of either `B` or `S`.
 * @pre @p cCargoId must have a character value of `C`, `R`, `S`, or `G`.
 * @return An integer value greater than `0`.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForCargoAmount(char cTransactionTypeId, int nShipCargoLimit, char cCargoId, int nPlayerBalance,
                               int nCoconutMarketPrice, int nRiceMarketPrice, int nSilkMarketPrice, int nGunMarketPrice,
                               int nShipCoconutCargoAmount, int nShipRiceCargoAmount, int nShipSilkCargoAmount,
                               int nShipGunCargoAmount);

/**
 * @brief Prompts the player to input a confirmation on whether they want to upgrade their ship or not.
 * @param nShipCurrentCargoLimit The current maximum amount of cargo that the ship can carry.
 * @param nPlayerBalance The player's gold coin balance.
 * @return `1` if the player wants to upgrade or `0` if they do not.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForShipUpgrade(int nShipCurrentCargoLimit, int nPlayerBalance);

/**
 * @brief Prompts the player to input the ID of the port they want to navigate to.
 * @param cCurrentPortId The ID of the current port.
 * @pre @p cCurrentPortId must have a character value of `T`, `M`, `P`, or `S`.
 * @return A character value of `T` for Tondo, `M` for Manila, `P` for Pandakan, `S` for Sapa, or `X` for returning to
 * the main menu.
 */
char promptPlayerForPortId(char cCurrentPortId);

#endif  // PROMPTS_H_
