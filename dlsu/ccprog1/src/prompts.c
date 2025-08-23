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

#include "prompts.h"

#include <ctype.h>
#include <stdio.h>

#include "console.h"
#include "trading.h"

/**
 * @brief Prompts the player to input their preferred merchant ID.
 * @return An integer value within the range of `0` and `999`.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForMerchantId(void) {
  int nConsoleLeftPaddingSize = 56;

  printf("%*cEnter your preferred merchant code (0 - 999)\n", nConsoleLeftPaddingSize, ' ');

  int nGivenMerchantId;
  int bIsValid = 0;

  do {
    nGivenMerchantId = getIntegerInput(nConsoleLeftPaddingSize);

    if (nGivenMerchantId < MINIMUM_MERCHANT_ID_VALUE || nGivenMerchantId > MAXIMUM_MERCHANT_ID_VALUE) {
      setConsoleColorToRed();
      printf("%*cPlease only enter an integer within the range of 0 - 999!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  return nGivenMerchantId;
}

/**
 * @brief Prompts the player to input the number of gold coins they want to start with.
 * @return An integer value greater than `0`.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForInitialBalance(void) {
  int nConsoleLeftPaddingSize = 57;

  printf("%*cEnter your preferred initial balance (> 0)\n", nConsoleLeftPaddingSize, ' ');

  int nGivenInitialBalance;
  int bIsValid = 0;

  do {
    nGivenInitialBalance = getIntegerInput(nConsoleLeftPaddingSize);

    if (nGivenInitialBalance < MINIMUM_INITIAL_BALANCE) {
      setConsoleColorToRed();
      printf("%*cPlease only enter an integer greater than 0!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  return nGivenInitialBalance;
}

/**
 * @brief Prompts the player to input their desired profit target.
 * @return An integer value greater than `20`.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForProfitTarget(void) {
  int nConsoleLeftPaddingSize = 62;

  printf("%*cEnter your target profit (>= 20)\n", nConsoleLeftPaddingSize, ' ');

  int nGivenProfitTarget;
  int bIsValid = 0;

  do {
    nGivenProfitTarget = getIntegerInput(nConsoleLeftPaddingSize);

    if (nGivenProfitTarget < MINIMUM_TARGET_PROFIT) {
      setConsoleColorToRed();
      printf("%*cPlease only enter an integer greater than or equal to 20!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  return nGivenProfitTarget;
}

/**
 * @brief Prompts the player to input a confirmation of their prior decision.
 * @return `1` if the player confirms or `0` if they do not.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForConfirmation(void) {
  int nConsoleLeftPaddingSize = 67;

  printf("%*cAre you sure? [Y / N]\n", nConsoleLeftPaddingSize, ' ');

  char cGivenBooleanId;
  int bIsValid = 0;

  do {
    cGivenBooleanId = toupper(getCharacterInput(nConsoleLeftPaddingSize));

    if (cGivenBooleanId != YES_ID && cGivenBooleanId != NO_ID) {
      setConsoleColorToRed();
      printf("%*cPlease only enter one of the provided character options!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  if (cGivenBooleanId == YES_ID) {
    return 1;
  } else {
    return 0;
  }
}

/** Prompts the player to press the enter or return key to continue the game. */
void promptPlayerForContinuation(void) {
  int nConsoleLeftPaddingSize = 62;

  printf("%*cEnter any character to continue\n", nConsoleLeftPaddingSize, ' ');

  getCharacterInput(nConsoleLeftPaddingSize);
}

/**
 * @brief Prompts the player to input the ID of the action they want to do.
 * @param nShipTotalCargoAmount The total amount of cargo carried by the ship.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 * @param nPlayerBalance The player's gold coin balance.
 * @param nCoconutMarketPrice The market price of coconuts.
 * @param nRiceMarketPrice The market price of rice.
 * @param nSilkMarketPrice The market price of silk.
 * @param nGunMarketPrice The market price of guns.
 * @return A character value of `B` for the buy screen, `S` for the sell screen, `U` for the ship upgrade screen, `N`
 * for the navigation screen, or `Q` for quitting the game.
 */
char promptPlayerForActionId(int nShipTotalCargoAmount, int nShipCargoLimit, int nPlayerBalance,
                             int nCoconutMarketPrice, int nRiceMarketPrice, int nSilkMarketPrice, int nGunMarketPrice) {
  int nConsoleLeftPaddingSize = 65;

  printf("%*cWhat would you like to do?\n", nConsoleLeftPaddingSize, ' ');

  if (nShipTotalCargoAmount < nShipCargoLimit &&
      (nPlayerBalance >= nCoconutMarketPrice || nPlayerBalance >= nRiceMarketPrice ||
       nPlayerBalance >= nSilkMarketPrice || nPlayerBalance >= nGunMarketPrice)) {
    printf("%*c‣ [B] Buy Cargo\n", nConsoleLeftPaddingSize, ' ');
  }

  if (nShipTotalCargoAmount > 0) {
    printf("%*c‣ [S] Sell Cargo\n", nConsoleLeftPaddingSize, ' ');
  }

  if (nShipCargoLimit < TIER_FOUR_SHIP_CARGO_LIMIT &&
      ((nShipCargoLimit == 75 && nPlayerBalance >= TIER_TWO_SHIP_UPGRADE_COST) ||
       (nShipCargoLimit == 150 && nPlayerBalance >= TIER_THREE_SHIP_UPGRADE_COST) ||
       (nShipCargoLimit == 225 && nPlayerBalance >= TIER_FOUR_SHIP_UPGRADE_COST))) {
    printf("%*c‣ [U] Upgrade Ship\n", nConsoleLeftPaddingSize, ' ');
  }

  printf("%*c‣ [N] Navigate To a Different Port\n", nConsoleLeftPaddingSize, ' ');

  printf("\n");

  printf("%*c‣ [Q] Quit Game\n", nConsoleLeftPaddingSize, ' ');

  char cChosenActionId;
  int bIsValid = 0;

  do {
    cChosenActionId = toupper(getCharacterInput(nConsoleLeftPaddingSize));

    if (cChosenActionId != BUY_ACTION_ID && cChosenActionId != SELL_ACTION_ID && cChosenActionId != UPGRADE_ACTION_ID &&
        cChosenActionId != NAVIGATE_ACTION_ID && cChosenActionId != QUIT_ACTION_ID) {
      setConsoleColorToRed();
      printf("%*cPlease only enter one of the provided character options!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenActionId == BUY_ACTION_ID && nShipTotalCargoAmount == nShipCargoLimit) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough storage to buy more cargo!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenActionId == BUY_ACTION_ID &&
               (nPlayerBalance <= nCoconutMarketPrice && nPlayerBalance <= nRiceMarketPrice &&
                nPlayerBalance <= nSilkMarketPrice && nPlayerBalance <= nGunMarketPrice)) {
      setConsoleColorToRed();
      printf("%*cYou can't afford to buy any cargo!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenActionId == SELL_ACTION_ID && nShipTotalCargoAmount == 0) {
      setConsoleColorToRed();
      printf("%*cYou have no cargo to sell!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenActionId == UPGRADE_ACTION_ID && nShipCargoLimit == TIER_FOUR_SHIP_CARGO_LIMIT) {
      setConsoleColorToRed();
      printf("%*cYour ship is already in the highest tier!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenActionId == UPGRADE_ACTION_ID &&
               ((nShipCargoLimit == 75 && nPlayerBalance < TIER_TWO_SHIP_UPGRADE_COST) ||
                (nShipCargoLimit == 150 && nPlayerBalance < TIER_THREE_SHIP_UPGRADE_COST) ||
                (nShipCargoLimit == 225 && nPlayerBalance < TIER_FOUR_SHIP_UPGRADE_COST))) {
      setConsoleColorToRed();
      printf("%*cYou can't afford to upgrade your ship!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  return cChosenActionId;
}

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
 * @return A character value of `C` for coconut, `R` for rice, `S` for silk, `G` for gun, or `X` for returning to the
 * main menu.
 */
char promptPlayerForCargoId(char cTransactionTypeId, int nPlayerBalance, int nCoconutMarketPrice, int nRiceMarketPrice,
                            int nSilkMarketPrice, int nGunMarketPrice, int nShipCoconutCargoAmount,
                            int nShipRiceCargoAmount, int nShipSilkCargoAmount, int nShipGunCargoAmount) {
  int nConsoleLeftPaddingSize = 64;

  if (cTransactionTypeId == BUY_ACTION_ID) {
    printf("%*cWhat would you like to buy?\n", nConsoleLeftPaddingSize, ' ');
  } else {
    printf("%*cWhat would you like to sell?\n", nConsoleLeftPaddingSize, ' ');
  }

  if (cTransactionTypeId == BUY_ACTION_ID) {
    if (nPlayerBalance > nCoconutMarketPrice) {
      printf("%*c‣ [C] Coconut\n", nConsoleLeftPaddingSize, ' ');
    }

    if (nPlayerBalance > nRiceMarketPrice) {
      printf("%*c‣ [R] Rice\n", nConsoleLeftPaddingSize, ' ');
    }

    if (nPlayerBalance > nSilkMarketPrice) {
      printf("%*c‣ [S] Silk\n", nConsoleLeftPaddingSize, ' ');
    }

    if (nPlayerBalance > nGunMarketPrice) {
      printf("%*c‣ [G] Gun\n", nConsoleLeftPaddingSize, ' ');
    }
  } else {
    if (nShipCoconutCargoAmount > 0) {
      printf("%*c‣ [C] Coconut\n", nConsoleLeftPaddingSize, ' ');
    }

    if (nShipRiceCargoAmount > 0) {
      printf("%*c‣ [R] Rice\n", nConsoleLeftPaddingSize, ' ');
    }

    if (nShipSilkCargoAmount > 0) {
      printf("%*c‣ [S] Silk\n", nConsoleLeftPaddingSize, ' ');
    }

    if (nShipGunCargoAmount > 0) {
      printf("%*c‣ [G] Gun\n", nConsoleLeftPaddingSize, ' ');
    }
  }

  printf("\n");

  printf("%*c‣ [X] Return To Main Menu\n", nConsoleLeftPaddingSize, ' ');

  char cChosenCargoId;
  int bIsValid = 0;

  do {
    cChosenCargoId = toupper(getCharacterInput(nConsoleLeftPaddingSize));

    if (cChosenCargoId != COCONUT_CARGO_ID && cChosenCargoId != RICE_CARGO_ID && cChosenCargoId != SILK_CARGO_ID &&
        cChosenCargoId != GUN_CARGO_ID && cChosenCargoId != CANCEL_ACTION_ID) {
      setConsoleColorToRed();
      printf("%*cPlease only enter one of the provided character options!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cChosenCargoId == COCONUT_CARGO_ID &&
               nPlayerBalance < nCoconutMarketPrice) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy a coconut!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cChosenCargoId == RICE_CARGO_ID &&
               nPlayerBalance < nRiceMarketPrice) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy rice!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cChosenCargoId == SILK_CARGO_ID &&
               nPlayerBalance < nSilkMarketPrice) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy silk!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cChosenCargoId == 'G' && nPlayerBalance < nGunMarketPrice) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy a gun!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cChosenCargoId == COCONUT_CARGO_ID &&
               nShipCoconutCargoAmount == 0) {
      setConsoleColorToRed();
      printf("%*cYou do not have any coconuts to sell!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cChosenCargoId == RICE_CARGO_ID && nShipRiceCargoAmount == 0) {
      setConsoleColorToRed();
      printf("%*cYou do not have any rice to sell!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cChosenCargoId == SILK_CARGO_ID && nShipSilkCargoAmount == 0) {
      setConsoleColorToRed();
      printf("%*cYou do not have any silk to sell!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cChosenCargoId == GUN_CARGO_ID && nShipGunCargoAmount == 0) {
      setConsoleColorToRed();
      printf("%*cYou do not have any guns to sell!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  return cChosenCargoId;
}

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
                               int nShipGunCargoAmount) {
  int nConsoleLeftPaddingSize = 57;

  if (cTransactionTypeId == BUY_ACTION_ID) {
    printf("%*cEnter the amount of cargo you want to buy\n", nConsoleLeftPaddingSize, ' ');
  } else {
    printf("%*cEnter the amount of cargo you want to sell\n", nConsoleLeftPaddingSize, ' ');
  }

  int nGivenCargoAmount;
  int bIsValid = 0;

  do {
    nGivenCargoAmount = getIntegerInput(nConsoleLeftPaddingSize);

    if (nGivenCargoAmount < 1) {
      setConsoleColorToRed();
      printf("%*cPlease only enter an integer greater than 0!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (nGivenCargoAmount > nShipCargoLimit) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough storage to buy this amount of cargo!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cCargoId == COCONUT_CARGO_ID &&
               nPlayerBalance < (nGivenCargoAmount * nCoconutMarketPrice)) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy %d coconuts!\n", nConsoleLeftPaddingSize, ' ',
             nGivenCargoAmount);
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cCargoId == RICE_CARGO_ID &&
               nPlayerBalance < (nGivenCargoAmount * nRiceMarketPrice)) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy %d rice!\n", nConsoleLeftPaddingSize, ' ', nGivenCargoAmount);
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cCargoId == SILK_CARGO_ID &&
               nPlayerBalance < (nGivenCargoAmount * nSilkMarketPrice)) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy %d silk!\n", nConsoleLeftPaddingSize, ' ', nGivenCargoAmount);
      resetConsoleColor();
    } else if (cTransactionTypeId == BUY_ACTION_ID && cCargoId == GUN_CARGO_ID &&
               nPlayerBalance < (nGivenCargoAmount * nGunMarketPrice)) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to buy %d guns!\n", nConsoleLeftPaddingSize, ' ', nGivenCargoAmount);
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cCargoId == COCONUT_CARGO_ID &&
               nShipCoconutCargoAmount < nGivenCargoAmount) {
      setConsoleColorToRed();
      printf("%*cYou do not have %d coconuts to sell!\n", nConsoleLeftPaddingSize, ' ', nGivenCargoAmount);
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cCargoId == RICE_CARGO_ID &&
               nShipRiceCargoAmount < nGivenCargoAmount) {
      setConsoleColorToRed();
      printf("%*cYou do not have %d rice to sell!\n", nConsoleLeftPaddingSize, ' ', nGivenCargoAmount);
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cCargoId == SILK_CARGO_ID &&
               nShipSilkCargoAmount < nGivenCargoAmount) {
      setConsoleColorToRed();
      printf("%*cYou do not have %d silk to sell!\n", nConsoleLeftPaddingSize, ' ', nGivenCargoAmount);
      resetConsoleColor();
    } else if (cTransactionTypeId == SELL_ACTION_ID && cCargoId == GUN_CARGO_ID &&
               nShipGunCargoAmount < nGivenCargoAmount) {
      setConsoleColorToRed();
      printf("%*cYou do not have %d guns to sell!\n", nConsoleLeftPaddingSize, ' ', nGivenCargoAmount);
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  return nGivenCargoAmount;
}

/**
 * @brief Prompts the player to input a confirmation on whether they want to upgrade their ship or
 * not.
 * @param nShipCurrentCargoLimit The current maximum amount of cargo that the ship can carry.
 * @param nPlayerBalance The player's gold coin balance.
 * @return `1` if the player wants to upgrade or `0` if they do not.
 * @bug Inputting a character or a string, or even just a long integer or float, as a response will result in an
 * infinite loop because the buffer cannot be cleared with any of the prescribed functions.
 */
int promptPlayerForShipUpgrade(int nShipCurrentCargoLimit, int nPlayerBalance) {
  int nConsoleLeftPaddingSize = 57;

  printf("%*cDo you want to upgrade your ship? [Y / N]\n", nConsoleLeftPaddingSize, ' ');

  char cGivenBooleanId;
  int bIsValid = 0;

  do {
    cGivenBooleanId = toupper(getCharacterInput(nConsoleLeftPaddingSize));

    if (cGivenBooleanId != YES_ID && cGivenBooleanId != NO_ID) {
      setConsoleColorToRed();
      printf("%*cPlease only enter one of the provided character options!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if ((nShipCurrentCargoLimit == TIER_ONE_SHIP_CARGO_LIMIT && nPlayerBalance < TIER_TWO_SHIP_UPGRADE_COST) ||
               (nShipCurrentCargoLimit == TIER_TWO_SHIP_CARGO_LIMIT && nPlayerBalance < TIER_THREE_SHIP_UPGRADE_COST) ||
               (nShipCurrentCargoLimit == TIER_THREE_SHIP_CARGO_LIMIT &&
                nPlayerBalance < TIER_FOUR_SHIP_UPGRADE_COST)) {
      setConsoleColorToRed();
      printf("%*cYou do not have enough gold coins to upgrade your ship!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  if (cGivenBooleanId == YES_ID) {
    return 1;
  } else {
    return 0;
  }
}

/**
 * @brief Prompts the player to input the ID of the port they want to navigate to.
 * @param cCurrentPortId The ID of the current port.
 * @pre @p cCurrentPortId must have a character value of `T`, `M`, `P`, or `S`.
 * @return A character value of `T` for Tondo, `M` for Manila, `P` for Pandakan, `S` for Sapa, or `X` for returning to
 * the main menu.
 */
char promptPlayerForPortId(char cCurrentPortId) {
  int nConsoleLeftPaddingSize = 64;

  printf("%*cWhere would you like to go?\n", nConsoleLeftPaddingSize, ' ');

  if (cCurrentPortId != 'T') {
    printf("%*c‣ [T] Tondo \n", nConsoleLeftPaddingSize, ' ');
  }

  if (cCurrentPortId != 'M') {
    printf("%*c‣ [M] Manila \n", nConsoleLeftPaddingSize, ' ');
  }

  if (cCurrentPortId != 'P') {
    printf("%*c‣ [P] Pandakan\n", nConsoleLeftPaddingSize, ' ');
  }

  if (cCurrentPortId != 'S') {
    printf("%*c‣ [S] Sapa\n", nConsoleLeftPaddingSize, ' ');
  }

  printf("\n");

  printf("%*c‣ [X] Return To Main Menu\n", nConsoleLeftPaddingSize, ' ');

  char cChosenPortId;
  int bIsValid = 0;

  do {
    cChosenPortId = toupper(getCharacterInput(nConsoleLeftPaddingSize));

    if (cChosenPortId != TONDO_PORT_ID && cChosenPortId != MANILA_PORT_ID && cChosenPortId != PANDAKAN_PORT_ID &&
        cChosenPortId != SAPA_PORT_ID && cChosenPortId != CANCEL_ACTION_ID) {
      setConsoleColorToRed();
      printf("%*cPlease only enter one of the provided character options!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenPortId == TONDO_PORT_ID && cCurrentPortId == TONDO_PORT_ID) {
      setConsoleColorToRed();
      printf("%*cYou are already in the port of Tondo!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenPortId == MANILA_PORT_ID && cCurrentPortId == MANILA_PORT_ID) {
      setConsoleColorToRed();
      printf("%*cYou are already in the port of Manila!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenPortId == PANDAKAN_PORT_ID && cCurrentPortId == PANDAKAN_PORT_ID) {
      setConsoleColorToRed();
      printf("%*cYou are already in the port of Pandakan!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else if (cChosenPortId == SAPA_PORT_ID && cCurrentPortId == SAPA_PORT_ID) {
      setConsoleColorToRed();
      printf("%*cYou are already in the port of Sapa!\n", nConsoleLeftPaddingSize, ' ');
      resetConsoleColor();
    } else {
      bIsValid = 1;
    }
  } while (!bIsValid);

  return cChosenPortId;
}
