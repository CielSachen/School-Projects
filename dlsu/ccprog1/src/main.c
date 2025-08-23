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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "console.h"
#include "prompts.h"
#include "text_graphics.h"
#include "trading.h"
#include "weather.h"

#define MAXIMUM_PLAYER_TURNS 31

int main(void) {
  srand(time(NULL));

  printGameStartScreen();

  int nPlayerMerchantId;
  int nPlayerInitialBalance;
  int nPlayerBalance;
  int nPlayerProfitTarget;

  nPlayerMerchantId = promptPlayerForMerchantId();

  printf("\n");

  nPlayerInitialBalance = promptPlayerForInitialBalance();
  nPlayerBalance = nPlayerInitialBalance;

  printf("\n");

  nPlayerProfitTarget = promptPlayerForProfitTarget();

  int nPlayerTurns = 0;
  int bIsQuitting = 0;
  char cCurrentPortId = 'M';
  int nPlayerProfit = 0;
  int nShipCargoLimit = TIER_ONE_SHIP_CARGO_LIMIT;
  int nShipCoconutCargoAmount = 0;
  int nShipRiceCargoAmount = 0;
  int nShipSilkCargoAmount = 0;
  int nShipGunCargoAmount = 0;
  int nStormTurnDuration = 0;
  int bIsNewStorm;
  int nStormWindSignalNumber;
  int nPostponedDepartureChance = DEFAULT_POSTPONED_DEPARTURE_CHANCE;

  while (nPlayerTurns < MAXIMUM_PLAYER_TURNS && !bIsQuitting) {
    int nCoconutMarketPrice;
    int nRiceMarketPrice;
    int nSilkMarketPrice;
    int nGunMarketPrice;

    if (cCurrentPortId == 'T') {
      nCoconutMarketPrice = generateRandomPrice(TONDO_MINIMUM_COCONUT_PRICE, TONDO_MAXIMUM_COCONUT_PRICE);
      nRiceMarketPrice = generateRandomPrice(TONDO_MINIMUM_RICE_PRICE, TONDO_MAXIMUM_RICE_PRICE);
      nSilkMarketPrice = generateRandomPrice(TONDO_MINIMUM_SILK_PRICE, TONDO_MAXIMUM_SILK_PRICE);
      nGunMarketPrice = generateRandomPrice(TONDO_MINIMUM_GUN_PRICE, TONDO_MAXIMUM_GUN_PRICE);
    } else if (cCurrentPortId == 'M') {
      nCoconutMarketPrice = generateRandomPrice(MANILA_MINIMUM_COCONUT_PRICE, MANILA_MAXIMUM_COCONUT_PRICE);
      nRiceMarketPrice = generateRandomPrice(MANILA_MINIMUM_RICE_PRICE, MANILA_MAXIMUM_RICE_PRICE);
      nSilkMarketPrice = generateRandomPrice(MANILA_MINIMUM_SILK_PRICE, MANILA_MAXIMUM_SILK_PRICE);
      nGunMarketPrice = generateRandomPrice(MANILA_MINIMUM_GUN_PRICE, MANILA_MAXIMUM_GUN_PRICE);
    } else if (cCurrentPortId == 'P') {
      nCoconutMarketPrice = generateRandomPrice(PANDAKAN_MINIMUM_COCONUT_PRICE, PANDAKAN_MAXIMUM_COCONUT_PRICE);
      nRiceMarketPrice = generateRandomPrice(PANDAKAN_MINIMUM_RICE_PRICE, PANDAKAN_MAXIMUM_RICE_PRICE);
      nSilkMarketPrice = generateRandomPrice(PANDAKAN_MINIMUM_SILK_PRICE, PANDAKAN_MAXIMUM_SILK_PRICE);
      nGunMarketPrice = generateRandomPrice(PANDAKAN_MINIMUM_GUN_PRICE, PANDAKAN_MAXIMUM_GUN_PRICE);
    } else {
      nCoconutMarketPrice = generateRandomPrice(SAPA_MINIMUM_COCONUT_PRICE, SAPA_MAXIMUM_COCONUT_PRICE);
      nRiceMarketPrice = generateRandomPrice(SAPA_MINIMUM_RICE_PRICE, SAPA_MAXIMUM_RICE_PRICE);
      nSilkMarketPrice = generateRandomPrice(SAPA_MINIMUM_SILK_PRICE, SAPA_MAXIMUM_SILK_PRICE);
      nGunMarketPrice = generateRandomPrice(SAPA_MINIMUM_GUN_PRICE, SAPA_MAXIMUM_GUN_PRICE);
    }

    int bIsNavigating = 0;

    while (!bIsNavigating && !bIsQuitting) {
      nPlayerProfit = ((nPlayerBalance - nPlayerInitialBalance) / (nPlayerInitialBalance * 1.0)) * 100;

      int nShipTotalCargoAmount =
        nShipCoconutCargoAmount + nShipRiceCargoAmount + nShipSilkCargoAmount + nShipGunCargoAmount;

      printMainScreen(nPlayerTurns, cCurrentPortId, nPlayerMerchantId, nPlayerBalance, nPlayerProfit,
                      nPlayerProfitTarget, nShipTotalCargoAmount, nShipCargoLimit, nShipCoconutCargoAmount,
                      nShipRiceCargoAmount, nShipSilkCargoAmount, nShipGunCargoAmount, nCoconutMarketPrice,
                      nRiceMarketPrice, nSilkMarketPrice, nGunMarketPrice);

      char cChosenActionId =
        promptPlayerForActionId(nShipTotalCargoAmount, nShipCargoLimit, nPlayerBalance, nCoconutMarketPrice,
                                nRiceMarketPrice, nSilkMarketPrice, nGunMarketPrice);

      printf("\n");

      if (cChosenActionId == 'B' || cChosenActionId == 'S') {
        char cChosenCargoId = promptPlayerForCargoId(
          cChosenActionId, nPlayerBalance, nShipCoconutCargoAmount, nRiceMarketPrice, nSilkMarketPrice, nGunMarketPrice,
          nShipCoconutCargoAmount, nShipRiceCargoAmount, nShipSilkCargoAmount, nShipGunCargoAmount);

        if (cChosenCargoId != 'X') {
          printf("\n");

          int nCargoAmount = promptPlayerForCargoAmount(
            cChosenActionId, nShipCargoLimit - nShipTotalCargoAmount, cChosenCargoId, nPlayerBalance,
            nCoconutMarketPrice, nRiceMarketPrice, nSilkMarketPrice, nGunMarketPrice, nShipCoconutCargoAmount,
            nShipRiceCargoAmount, nShipSilkCargoAmount, nShipGunCargoAmount);

          printf("\n");

          int bIsConfirmed = promptPlayerForConfirmation();

          if (bIsConfirmed) {
            int nCargoPrice;
            int* nShipCargoAmount;

            if (cChosenCargoId == 'C') {
              nCargoPrice = nCoconutMarketPrice;
              nShipCargoAmount = &nShipCoconutCargoAmount;
            } else if (cChosenCargoId == 'R') {
              nCargoPrice = nRiceMarketPrice;
              nShipCargoAmount = &nShipRiceCargoAmount;
            } else if (cChosenCargoId == 'S') {
              nCargoPrice = nSilkMarketPrice;
              nShipCargoAmount = &nShipSilkCargoAmount;
            } else {
              nCargoPrice = nGunMarketPrice;
              nShipCargoAmount = &nShipGunCargoAmount;
            }

            tradeCargo(cChosenActionId, &nPlayerBalance, nCargoPrice, nCargoAmount, nShipCargoAmount);

            printTransactionScreen(cChosenActionId, cChosenCargoId, nCargoAmount, nCargoPrice);

            promptPlayerForContinuation();
          }
        }
      } else if (cChosenActionId == 'U') {
        printShipUpgradeMenu(nShipCargoLimit);

        int bIsUpgrading = promptPlayerForShipUpgrade(nShipCargoLimit, nPlayerBalance);

        if (bIsUpgrading) {
          int nShipUpgradeCost;
          int nShipNewCargoLimit;
          int nShipCargoLimitIncrease;

          if (nShipCargoLimit == TIER_ONE_SHIP_CARGO_LIMIT) {
            nShipUpgradeCost = TIER_TWO_SHIP_UPGRADE_COST;
            nShipNewCargoLimit = TIER_TWO_SHIP_CARGO_LIMIT;
            nShipCargoLimitIncrease = nShipNewCargoLimit - nShipCargoLimit;
          } else if (nShipCargoLimit == TIER_TWO_SHIP_CARGO_LIMIT) {
            nShipUpgradeCost = TIER_THREE_SHIP_UPGRADE_COST;
            nShipNewCargoLimit = TIER_THREE_SHIP_CARGO_LIMIT;
            nShipCargoLimitIncrease = nShipNewCargoLimit - nShipCargoLimit;
          } else {
            nShipUpgradeCost = TIER_FOUR_SHIP_UPGRADE_COST;
            nShipNewCargoLimit = TIER_FOUR_SHIP_CARGO_LIMIT;
            nShipCargoLimitIncrease = nShipNewCargoLimit - nShipCargoLimit;
          }

          upgradeShip(&nPlayerBalance, nShipUpgradeCost, &nShipCargoLimit, nShipNewCargoLimit);

          printShipUpgradeScreen(nShipCargoLimitIncrease, nShipUpgradeCost);

          promptPlayerForContinuation();
        }
      } else if (cChosenActionId == 'N') {
        printNavigationMenu(cCurrentPortId, nPlayerTurns);

        char cChosenPortId = promptPlayerForPortId(cCurrentPortId);

        if (cChosenPortId != 'X') {
          printf("\n");

          int bIsConfirmed = promptPlayerForConfirmation();

          if (bIsConfirmed) {
            int bIsSuccessful = generateRandomBool(100 - nPostponedDepartureChance);

            if (bIsSuccessful) {
              cCurrentPortId = cChosenPortId;

              printNavigationScreen(bIsSuccessful, cCurrentPortId, nPlayerTurns);
            } else {
              printNavigationScreen(bIsSuccessful, cChosenPortId, nPlayerTurns);
            }

            promptPlayerForContinuation();

            nPlayerTurns++;
            bIsNavigating = 1;
          }
        }
      } else {
        bIsQuitting = 1;
      }
    }

    if (!bIsQuitting) {
      if (nStormTurnDuration == -1) {
        nStormTurnDuration = 0;
      } else if (nStormTurnDuration == 0) {
        int bStartStorm = generateRandomBool(50);

        if (bStartStorm) {
          nStormTurnDuration = generateRandomStormTurnDuration(1) + 1;
          nStormWindSignalNumber = 1;
          bIsNewStorm = 1;
        }
      }

      if (nStormTurnDuration > 0) {
        nStormTurnDuration--;

        int nStormOldWindSignalNumber = nStormWindSignalNumber;

        if (nStormTurnDuration == 0) {
          nPostponedDepartureChance = 0;

          nStormTurnDuration--;
        } else if (!bIsNewStorm && (nStormWindSignalNumber < 5)) {
          int bAdjustStormStrength = generateRandomBool(50);

          if (bAdjustStormStrength) {
            int nStormNewWindSignalNumber;

            if (nStormWindSignalNumber < 5) {
              nStormNewWindSignalNumber = nStormWindSignalNumber + 1;
            } else {
              nStormNewWindSignalNumber = nStormWindSignalNumber - 1;
            }

            setStormStrength(&nStormWindSignalNumber, nStormNewWindSignalNumber, &nPostponedDepartureChance);
          }
        }

        printWeatherReportScreen(bIsNewStorm, nStormOldWindSignalNumber, nStormWindSignalNumber,
                                 nPostponedDepartureChance, nStormTurnDuration);

        if (bIsNewStorm) {
          bIsNewStorm = 0;
        }

        promptPlayerForContinuation();
      }
    }
  }

  printGameEndScreen(nPlayerProfit, nPlayerProfitTarget, nPlayerBalance, nPlayerInitialBalance, nPlayerTurns);

  return 0;
}
