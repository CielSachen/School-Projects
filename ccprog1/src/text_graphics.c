/*
 * Tides of Manila: A Merchant's Quest is a turn-based CLI-based game.
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
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "text_graphics.h"

#include <stdio.h>

#include "console.h"
#include "prompts.h"
#include "trading.h"

/** @brief Prints out a pre-formatted separator line to the console. */
void printSeparator(void) {
    printf("\n\n\n");

    for (int nPrintedDashCount = 0; nPrintedDashCount < CONSOLE_MAX_WIDTH; nPrintedDashCount++) {
        printf("━");
    }

    printf("\n\n\n\n");
}

/** @brief Prints out the game's start screen, which contains the game's title, to the console. */
void printGameStartScreen(void) {
    printSeparator();

    printf(
        "     ███      ▄█  ████████▄     ▄████████    ▄████████       ▄██████▄     ▄████████        ▄▄▄▄███▄▄▄▄      ▄████████ ███▄▄▄▄    ▄█   ▄█          ▄████████\n"
        " ▀█████████▄ ███  ███   ▀███   ███    ███   ███    ███      ███    ███   ███    ███      ▄██▀▀▀███▀▀▀██▄   ███    ███ ███▀▀▀██▄ ███  ███         ███    ███\n"
        "    ▀███▀▀██ ███▌ ███    ███   ███    █▀    ███    █▀       ███    ███   ███    █▀       ███   ███   ███   ███    ███ ███   ███ ███▌ ███         ███    ███\n"
        "     ███   ▀ ███▌ ███    ███  ▄███▄▄▄       ███             ███    ███  ▄███▄▄▄          ███   ███   ███   ███    ███ ███   ███ ███▌ ███         ███    ███\n"
        "     ███     ███▌ ███    ███ ▀▀███▀▀▀     ▀███████████      ███    ███ ▀▀███▀▀▀          ███   ███   ███ ▀███████████ ███   ███ ███▌ ███       ▀███████████\n"
        "     ███     ███  ███    ███   ███    █▄           ███      ███    ███   ███             ███   ███   ███   ███    ███ ███   ███ ███  ███         ███    ███\n"
        "     ███     ███  ███   ▄███   ███    ███    ▄█    ███      ███    ███   ███             ███   ███   ███   ███    ███ ███   ███ ███  ███▌    ▄   ███    ███\n"
        "    ▄████▀   █▀   ████████▀    ██████████  ▄████████▀        ▀██████▀    ███              ▀█   ███   █▀    ███    █▀   ▀█   █▀  █▀   █████▄▄██   ███    █▀\n"
        "                                                                                                                                     ▀\n");

    printf("\n");

    printf(
        "                                    ▗▄▖     ▗▖  ▗▖▗▄▄▄▖▗▄▄▖  ▗▄▄▖▗▖ ▗▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖▗▄▄▖    ▗▄▄▄▖ ▗▖ ▗▖▗▄▄▄▖ ▗▄▄▖▗▄▄▄▖\n"
        "                                   ▐▌ ▐▌    ▐▛▚▞▜▌▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▛▚▖▐▌  █ ▐▌       ▐▌ ▐▌ ▐▌ ▐▌▐▌   ▐▌     █\n"
        "                                   ▐▛▀▜▌    ▐▌  ▐▌▐▛▀▀▘▐▛▀▚▖▐▌   ▐▛▀▜▌▐▛▀▜▌▐▌ ▝▜▌  █  ▝▀▚▖    ▐▌ ▐▌ ▐▌ ▐▌▐▛▀▀▘ ▝▀▚▖  █\n"
        "                                   ▐▌ ▐▌    ▐▌  ▐▌▐▙▄▄▖▐▌ ▐▌▝▚▄▄▖▐▌ ▐▌▐▌ ▐▌▐▌  ▐▌  █ ▗▄▄▞▘    ▐▙▄▟▙▖▝▚▄▞▘▐▙▄▄▖▗▄▄▞▘  █\n");

    printf("\n\n\n\n\n");
}

/**
 * @brief Prints out a ship's sprite based on the passed cargo limit of the player's ship.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 */
void printShipSprite(int nShipCargoLimit) {
    if (nShipCargoLimit <= TIER_ONE_SHIP_CARGO_LIMIT) {
        printf(
            "                                                               ~~~\n"
            "                                                          ~~~~     ~~~~        |\n"
            "                                                               ~~~            /|\n"
            "                                                                             / |\\\n"
            "                                                                            /  | \\\n"
            "                                                                           /   |  \\\n"
            "                                                                          /    |   \\\n"
            "                                                                         /     |____\\\n"
            "                                                                   _____/______|_________\n"
            "                                                                    \\__________________/\n"
            "                                                            ~~..             ...~~~.           ....~~~...\n");
    } else if (nShipCargoLimit <= TIER_TWO_SHIP_CARGO_LIMIT) {
        printf(
            "                                                          ~~~\n"
            "                                                     ~~~~     ~~~~       |\n"
            "                                                          ~~~          -----        |\n"
            "                                                                       )___(        |\\\n"
            "                                                                         |          | \\\n"
            "                                                                      -------       |  \\\n"
            "                                                                     /       \\      |   \\\n"
            "                                                                    /_________\\     |____\\\n"
            "                                                              ___________|__________|_________\n"
            "                                                               \\____________________________/\n"
            "                                                       ~~..             ...~~~.           ....~~~...     ..~\n");
    } else if (nShipCargoLimit <= TIER_THREE_SHIP_CARGO_LIMIT) {
        printf(
            "                                                      ~~~             |\n"
            "                                                 ~~~~     ~~~~      -----              |\n"
            "                                                      ~~~           )___(            -----\n"
            "                                                                      |              )___(\n"
            "                                                                  ---------            |\n"
            "                                                                 /         \\        -------\n"
            "                                                                /           \\      /       \\\n"
            "                                                               /_____________\\    /_________\\\n"
            "                                                          ____________|________________|__________\n"
            "                                                           \\_                                  _/\n"
            "                                                             \\________________________________/\n"
            "                                                   ~~..             ...~~~.           ....~~~...     ..~\n");
    } else {
        printf(
            "                                                   ~~~             |\n"
            "                                              ~~~~     ~~~~      -----                    |\n"
            "                                                   ~~~           )___(                  -----\n"
            "                                                                   |                    )___(\n"
            "                                                               ---------                  |\n"
            "                                                              /         \\              -------\n"
            "                                                             /___________\\            /       \\\n"
            "                                                                   |                 /_________\\\n"
            "                                                            ---------------               |\n"
            "                                                           /               \\        -------------\n"
            "                                                          /                 \\      /             \\\n"
            "                                                         /___________________\\    /_______________\\\n"
            "                                                       ____________|______________________|__________\n"
            "                                                        \\_                                        _/\n"
            "                                                          \\______________________________________/\n"
            "                                                   ~~..             ...~~~.           ....~~~...     ..~\n");
    }
}

/**
 * @brief Prints out the game's main menu screen, which contains statistics about the player and
 * their ship and the port's cargo market prices, to the console.
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
void printMainScreen(int nPlayerTurns, char cPortId, int nPlayerMerchantId, int nPlayerBalance,
                     int nPlayerProfit, int nPlayerProfitTarget, int nShipTotalCargoAmount,
                     int nShipCargoLimit, int nShipCoconutCargoAmount, int nShipRiceCargoAmount,
                     int nShipSilkCargoAmount, int nShipGunCargoAmount, int nCoconutMarketPrice,
                     int nRiceMarketPrice, int nSilkMarketPrice, int nGunMarketPrice) {
    printSeparator();

    switch (cPortId) {
        case 'T':
            printf(
                "                                                        ████████  ██████  ███    ██ ██████   ██████\n"
                "                                                           ██    ██    ██ ████   ██ ██   ██ ██    ██\n"
                "                                                           ██    ██    ██ ██ ██  ██ ██   ██ ██    ██\n"
                "                                                           ██    ██    ██ ██  ██ ██ ██   ██ ██    ██\n"
                "                                                           ██     ██████  ██   ████ ██████   ██████\n");

            break;

        case 'M':
            printf(
                "                                                      ███    ███  █████  ███    ██ ██ ██       █████\n"
                "                                                      ████  ████ ██   ██ ████   ██ ██ ██      ██   ██\n"
                "                                                      ██ ████ ██ ███████ ██ ██  ██ ██ ██      ███████\n"
                "                                                      ██  ██  ██ ██   ██ ██  ██ ██ ██ ██      ██   ██\n"
                "                                                      ██      ██ ██   ██ ██   ████ ██ ███████ ██   ██\n");

            break;

        case 'P':
            printf(
                "                                            ██████   █████  ███    ██ ██████   █████  ██   ██  █████  ███    ██\n"
                "                                            ██   ██ ██   ██ ████   ██ ██   ██ ██   ██ ██  ██  ██   ██ ████   ██\n"
                "                                            ██████  ███████ ██ ██  ██ ██   ██ ███████ █████   ███████ ██ ██  ██\n"
                "                                            ██      ██   ██ ██  ██ ██ ██   ██ ██   ██ ██  ██  ██   ██ ██  ██ ██\n"
                "                                            ██      ██   ██ ██   ████ ██████  ██   ██ ██   ██ ██   ██ ██   ████\n");

            break;

        case 'S':
            printf(
                "                                                                   ███████  █████  ██████   █████\n"
                "                                                                   ██      ██   ██ ██   ██ ██   ██\n"
                "                                                                   ███████ ███████ ██████  ███████\n"
                "                                                                        ██ ██   ██ ██      ██   ██\n"
                "                                                                   ███████ ██   ██ ██      ██   ██\n");

            break;
    }

    printf("\n\n");

    printf(
        "   • Merchant ID: %3d                                                                                              • Balance: %d Gold Coins\n"
        "   • Profit:",
        nPlayerMerchantId, nPlayerBalance);

    if (nPlayerProfit >= nPlayerProfitTarget) {
        setConsoleColorToGreen();
    } else {
        setConsoleColorToRed();
    }

    printf(" %d%%\n", nPlayerProfit);
    resetConsoleColor();

    printf("   • Target Profit %d%%\n", nPlayerProfitTarget);

    printf("\n\n");

    printShipSprite(nShipCargoLimit);

    printf("\n\n");

    printf(
        "   ║                                    ║                                                                          ║                                    ║\n"
        " ==X====================================X==                                                                      ==X====================================X==\n"
        "   ║    Total Cargo    |   %3d of %3d   ║                                                                          ║   Market Prices   |  Day %2d of 30  ║\n"
        "   ║----------- ------- -------- -------║                                                                          ║------------------- ----------------║\n"
        "   ║  Coconut  |  %3d  |  Silk  |  %3d  ║                                                                          ║  Coconut  |  %3d  |  Silk  |  %3d  ║\n"
        "   ║  Rice     |  %3d  |  Gun   |  %3d  ║                                                                          ║  Rice     |  %3d  |  Gun   |  %3d  ║\n"
        " ==X====================================X==                                                                      ==X====================================X==\n"
        "   ║                                    ║                                                                          ║                                    ║\n",
        nShipTotalCargoAmount, nShipCargoLimit, nPlayerTurns, nShipCoconutCargoAmount,
        nShipSilkCargoAmount, nCoconutMarketPrice, nSilkMarketPrice, nShipRiceCargoAmount,
        nShipGunCargoAmount, nRiceMarketPrice, nGunMarketPrice);

    printf("\n\n\n");
}

/**
 * @brief Prints out the game's transaction screen, which contains the name of the cargo that the
 * player traded and the number of gold coins the player has spent or earned, to the console.
 * @param cTransactionType The type of transaction made.
 * @param cCargoId The ID of the traded cargo.
 * @param nCargoAmount The amount of cargo to trade.
 * @param nCargoPrice The price of the cargo.
 * @pre @p cTransactionType must have a character value of either `B` or `S`.
 * @pre @p cCargoId must have a character value of `C`, `R`, `S`, or `G`.
 */
void printTransactionScreen(char cTransactionType, char cCargoId, int nCargoAmount,
                            int nCargoPrice) {
    printSeparator();

    int nConsoleLeftPaddingSize;

    if (cCargoId == 'C') {
        if (cTransactionType == BUY_ACTION_ID) {
            printf(
                "                                         ▗▄▄▖ ▗▄▖  ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▖ ▗▖▗▄▄▄▖ ▗▄▄▖    ▗▄▄▖  ▗▄▖ ▗▖ ▗▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖\n"
                "                                        ▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▛▚▖▐▌▐▌ ▐▌  █  ▐▌       ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌  █\n"
                "                                        ▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▝▜▌▐▌ ▐▌  █   ▝▀▚▖    ▐▛▀▚▖▐▌ ▐▌▐▌ ▐▌▐▌▝▜▌▐▛▀▜▌  █\n"
                "                                        ▝▚▄▄▖▝▚▄▞▘▝▚▄▄▖▝▚▄▞▘▐▌  ▐▌▝▚▄▞▘  █  ▗▄▄▞▘    ▐▙▄▞▘▝▚▄▞▘▝▚▄▞▘▝▚▄▞▘▐▌ ▐▌  █\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 40;

            setConsoleColorToGreen();
            printf("%*c• You added %d coconuts to the ship's storage!\n", nConsoleLeftPaddingSize,
                   ' ', nCargoAmount);
        } else {
            printf(
                "                                              ▗▄▄▖ ▗▄▖  ▗▄▄▖ ▗▄▖ ▗▖  ▗▖▗▖ ▗▖▗▄▄▄▖ ▗▄▄▖     ▗▄▄▖ ▗▄▖ ▗▖   ▗▄▄▄ \n"
                "                                             ▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▛▚▖▐▌▐▌ ▐▌  █  ▐▌       ▐▌   ▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                             ▐▌   ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▝▜▌▐▌ ▐▌  █   ▝▀▚▖     ▝▀▚▖▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                             ▝▚▄▄▖▝▚▄▞▘▝▚▄▄▖▝▚▄▞▘▐▌  ▐▌▝▚▄▞▘  █  ▗▄▄▞▘    ▗▄▄▞▘▝▚▄▞▘▐▙▄▄▖▐▙▄▄▀\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 45;

            setConsoleColorToRed();
            printf("%*c• You removed %d coconuts from the ship's storage.\n",
                   nConsoleLeftPaddingSize, ' ', nCargoAmount);
        }
    } else if (cCargoId == 'R') {
        if (cTransactionType == BUY_ACTION_ID) {
            printf(
                "                                                   ▗▄▄▖ ▗▄▄▄▖ ▗▄▄▖▗▄▄▄▖    ▗▄▄▖  ▗▄▖ ▗▖ ▗▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖\n"
                "                                                   ▐▌ ▐▌  █  ▐▌   ▐▌       ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌  █\n"
                "                                                   ▐▛▀▚▖  █  ▐▌   ▐▛▀▀▘    ▐▛▀▚▖▐▌ ▐▌▐▌ ▐▌▐▌▝▜▌▐▛▀▜▌  █\n"
                "                                                   ▐▌ ▐▌▗▄█▄▖▝▚▄▄▖▐▙▄▄▖    ▐▙▄▞▘▝▚▄▞▘▝▚▄▞▘▝▚▄▞▘▐▌ ▐▌  █\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 51;

            setConsoleColorToGreen();
            printf("%*c• You added %d rice to the ship's storage!\n", nConsoleLeftPaddingSize, ' ',
                   nCargoAmount);
        } else {
            printf(
                "                                                        ▗▄▄▖ ▗▄▄▄▖ ▗▄▄▖▗▄▄▄▖     ▗▄▄▖ ▗▄▖ ▗▖   ▗▄▄▄ \n"
                "                                                        ▐▌ ▐▌  █  ▐▌   ▐▌       ▐▌   ▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                                        ▐▛▀▚▖  █  ▐▌   ▐▛▀▀▘     ▝▀▚▖▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                                        ▐▌ ▐▌▗▄█▄▖▝▚▄▄▖▐▙▄▄▖    ▗▄▄▞▘▝▚▄▞▘▐▙▄▄▖▐▙▄▄▀\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 56;

            setConsoleColorToRed();
            printf("%*c• You removed %d rice from the ship's storage.\n", nConsoleLeftPaddingSize,
                   ' ', nCargoAmount);
        }
    } else if (cCargoId == 'S') {
        if (cTransactionType == BUY_ACTION_ID) {
            printf(
                "                                                    ▗▄▄▖▗▄▄▄▖▗▖   ▗▖ ▗▖    ▗▄▄▖  ▗▄▖ ▗▖ ▗▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖\n"
                "                                                   ▐▌     █  ▐▌   ▐▌▗▞▘    ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌  █\n"
                "                                                    ▝▀▚▖  █  ▐▌   ▐▛▚▖     ▐▛▀▚▖▐▌ ▐▌▐▌ ▐▌▐▌▝▜▌▐▛▀▜▌  █\n"
                "                                                   ▗▄▄▞▘▗▄█▄▖▐▙▄▄▖▐▌ ▐▌    ▐▙▄▞▘▝▚▄▞▘▝▚▄▞▘▝▚▄▞▘▐▌ ▐▌  █\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 51;

            setConsoleColorToGreen();
            printf("%*c• You added %d silk to the ship's storage!\n", nConsoleLeftPaddingSize, ' ',
                   nCargoAmount);
        } else {
            printf(
                "                                                         ▗▄▄▖▗▄▄▄▖▗▖   ▗▖ ▗▖     ▗▄▄▖ ▗▄▖ ▗▖   ▗▄▄▄ \n"
                "                                                        ▐▌     █  ▐▌   ▐▌▗▞▘    ▐▌   ▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                                         ▝▀▚▖  █  ▐▌   ▐▛▚▖      ▝▀▚▖▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                                        ▗▄▄▞▘▗▄█▄▖▐▙▄▄▖▐▌ ▐▌    ▗▄▄▞▘▝▚▄▞▘▐▙▄▄▖▐▙▄▄▀\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 56;

            setConsoleColorToRed();
            printf("%*c• You removed %d silk from the ship's storage.\n", nConsoleLeftPaddingSize,
                   ' ', nCargoAmount);
        }
    } else {
        if (cTransactionType == BUY_ACTION_ID) {
            printf(
                "                                                   ▗▄▄▖▗▖ ▗▖▗▖  ▗▖ ▗▄▄▖    ▗▄▄▖  ▗▄▖ ▗▖ ▗▖ ▗▄▄▖▗▖ ▗▖▗▄▄▄▖\n"
                "                                                  ▐▌   ▐▌ ▐▌▐▛▚▖▐▌▐▌       ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌  █\n"
                "                                                  ▐▌▝▜▌▐▌ ▐▌▐▌ ▝▜▌ ▝▀▚▖    ▐▛▀▚▖▐▌ ▐▌▐▌ ▐▌▐▌▝▜▌▐▛▀▜▌  █\n"
                "                                                  ▝▚▄▞▘▝▚▄▞▘▐▌  ▐▌▗▄▄▞▘    ▐▙▄▞▘▝▚▄▞▘▝▚▄▞▘▝▚▄▞▘▐▌ ▐▌  █\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 50;

            setConsoleColorToGreen();
            printf("%*c• You added %d guns to the ship's storage!\n", nConsoleLeftPaddingSize, ' ',
                   nCargoAmount);
        } else {
            printf(
                "                                                        ▗▄▄▖▗▖ ▗▖▗▖  ▗▖ ▗▄▄▖     ▗▄▄▖ ▗▄▖ ▗▖   ▗▄▄▄ \n"
                "                                                       ▐▌   ▐▌ ▐▌▐▛▚▖▐▌▐▌       ▐▌   ▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                                       ▐▌▝▜▌▐▌ ▐▌▐▌ ▝▜▌ ▝▀▚▖     ▝▀▚▖▐▌ ▐▌▐▌   ▐▌  █\n"
                "                                                       ▝▚▄▞▘▝▚▄▞▘▐▌  ▐▌▗▄▄▞▘    ▗▄▄▞▘▝▚▄▞▘▐▙▄▄▖▐▙▄▄▀\n");

            printf("\n\n");

            nConsoleLeftPaddingSize = 55;

            setConsoleColorToRed();
            printf("%*c• You removed %d guns from the ship's storage.\n", nConsoleLeftPaddingSize,
                   ' ', nCargoAmount);
        }
    }

    if (cTransactionType == BUY_ACTION_ID) {
        setConsoleColorToRed();
        printf("%*c• You spent %d gold coins.\n", nConsoleLeftPaddingSize, ' ',
               nCargoPrice * nCargoAmount);
        resetConsoleColor();
    } else {
        setConsoleColorToGreen();
        printf("%*c• You earned %d gold coins!\n", nConsoleLeftPaddingSize, ' ',
               nCargoPrice * nCargoAmount);
        resetConsoleColor();
    }

    printf("\n\n\n\n\n");
}

/**
 * @brief Prints out the game's ship upgrade menu, which contains a preview of the upgraded ship and
 * details about its cargo capacity and price, to the console.
 * @param nShipCargoLimit The maximum amount of cargo that the ship can carry.
 */
void printShipUpgradeMenu(int nShipCargoLimit) {
    printSeparator();

    printf(
        "                                                 ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▄▄▖     ▗▖ ▗▖▗▄▄▖  ▗▄▄▖▗▄▄▖  ▗▄▖ ▗▄▄▄ ▗▄▄▄▖\n"
        "                                                ▐▌   ▐▌ ▐▌  █  ▐▌ ▐▌    ▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌  █▐▌\n"
        "                                                 ▝▀▚▖▐▛▀▜▌  █  ▐▛▀▘     ▐▌ ▐▌▐▛▀▘ ▐▌▝▜▌▐▛▀▚▖▐▛▀▜▌▐▌  █▐▛▀▀▘\n"
        "                                                ▗▄▄▞▘▐▌ ▐▌▗▄█▄▖▐▌       ▝▚▄▞▘▐▌   ▝▚▄▞▘▐▌ ▐▌▐▌ ▐▌▐▙▄▄▀▐▙▄▄▖\n");

    printf("\n\n");

    int nShipUpgradeCost;
    int nShipNewCargoLimit;
    int nShipAdditionalCargoLimit;

    if (nShipCargoLimit == TIER_ONE_SHIP_CARGO_LIMIT) {
        printShipSprite(TIER_TWO_SHIP_CARGO_LIMIT);

        nShipUpgradeCost = TIER_TWO_SHIP_UPGRADE_COST;
        nShipNewCargoLimit = TIER_TWO_SHIP_CARGO_LIMIT;
        nShipAdditionalCargoLimit = TIER_TWO_SHIP_CARGO_LIMIT - TIER_ONE_SHIP_CARGO_LIMIT;
    } else if (nShipCargoLimit == TIER_TWO_SHIP_CARGO_LIMIT) {
        printShipSprite(TIER_THREE_SHIP_CARGO_LIMIT);

        nShipUpgradeCost = TIER_THREE_SHIP_UPGRADE_COST;
        nShipNewCargoLimit = TIER_THREE_SHIP_CARGO_LIMIT;
        nShipAdditionalCargoLimit = TIER_THREE_SHIP_CARGO_LIMIT - TIER_TWO_SHIP_CARGO_LIMIT;
    } else {
        printShipSprite(TIER_FOUR_SHIP_CARGO_LIMIT);

        nShipUpgradeCost = TIER_FOUR_SHIP_UPGRADE_COST;
        nShipNewCargoLimit = TIER_FOUR_SHIP_CARGO_LIMIT;
        nShipAdditionalCargoLimit = TIER_FOUR_SHIP_CARGO_LIMIT - TIER_THREE_SHIP_CARGO_LIMIT;
    }

    printf("\n\n");

    int nConsoleLeftPaddingSize = 48;

    printf(
        "%*c• Cost: %d\n"
        "%*c• Cargo Capacity: %d (+%d)\n",
        nConsoleLeftPaddingSize, ' ', nShipUpgradeCost, nConsoleLeftPaddingSize, ' ',
        nShipNewCargoLimit, nShipAdditionalCargoLimit);

    printf("\n\n\n");
}

/**
 * @brief Prints out the game's ship upgrade screen, which contains the number of additional cargo
 * spaces the ship has received and gold coins the player has spent, to the console.
 * @param nShipCargoLimitIncrease The amount of additional cargo space the ship has gotten.
 * @param nShipUpgradeCost The price of the ship upgrade.
 */
void printShipUpgradeScreen(int nShipCargoLimitIncrease, int nShipUpgradeCost) {
    printSeparator();

    printf(
        "                                               ▗▄▄▖▗▖ ▗▖▗▄▄▄▖▗▄▄▖     ▗▖ ▗▖▗▄▄▖  ▗▄▄▖▗▄▄▖  ▗▄▖ ▗▄▄▄ ▗▄▄▄▖▗▄▄▄\n"
        "                                              ▐▌   ▐▌ ▐▌  █  ▐▌ ▐▌    ▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌  █▐▌   ▐▌  █\n"
        "                                               ▝▀▚▖▐▛▀▜▌  █  ▐▛▀▘     ▐▌ ▐▌▐▛▀▘ ▐▌▝▜▌▐▛▀▚▖▐▛▀▜▌▐▌  █▐▛▀▀▘▐▌  █\n"
        "                                              ▗▄▄▞▘▐▌ ▐▌▗▄█▄▖▐▌       ▝▚▄▞▘▐▌   ▝▚▄▞▘▐▌ ▐▌▐▌ ▐▌▐▙▄▄▀▐▙▄▄▖▐▙▄▄▀\n");

    printf("\n\n");

    int nConsoleLeftPaddingSize = 46;

    setConsoleColorToGreen();
    printf("%*c• Your ship gained %d additional cargo spaces!\n", nConsoleLeftPaddingSize, ' ',
           nShipCargoLimitIncrease);
    resetConsoleColor();

    setConsoleColorToRed();
    printf("%*c• You spent %d gold coins.\n", nConsoleLeftPaddingSize, ' ', nShipUpgradeCost);
    resetConsoleColor();

    printf("\n\n\n\n\n");
}

/**
 * @brief Prints out the game's navigation menu, which contains the navigation map, to the console.
 * @param cCurrentPortId The current port's ID.
 * @param nPlayerTurns The number of turns the player has exhausted.
 * @pre @p cCurrentPortId must have a character value of `T`, `M`, `P`, or `S`.
 * @pre @p nPlayerTurns must have a a 2-digit positive integer value.
 */
void printNavigationMenu(char cCurrentPortId, int nPlayerTurns) {
    printSeparator();

    printf(
        "                                                    ▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖ ▗▄▖▗▄▄▄▖▗▄▄▄▖ ▗▄▖ ▗▖  ▗▖\n"
        "                                                    ▐▛▚▖▐▌▐▌ ▐▌▐▌  ▐▌  █  ▐▌   ▐▌ ▐▌ █    █  ▐▌ ▐▌▐▛▚▖▐▌\n"
        "                                                    ▐▌ ▝▜▌▐▛▀▜▌▐▌  ▐▌  █  ▐▌▝▜▌▐▛▀▜▌ █    █  ▐▌ ▐▌▐▌ ▝▜▌\n"
        "                                                    ▐▌  ▐▌▐▌ ▐▌ ▝▚▞▘ ▗▄█▄▖▝▚▄▞▘▐▌ ▐▌ █  ▗▄█▄▖▝▚▄▞▘▐▌  ▐▌\n");

    printf("\n\n");

    printf("%*cDay %2d of 30\n", 72, ' ', nPlayerTurns);

    printf("\n");

    switch (cCurrentPortId) {
            // clang-format off
    case 'T': 
      printf(
        "                                           You are here!\n"
        "                                                 ↓\n"
        "                                               Tondo\n"
        "                                                 ◯\n" COLOR_BLUE
        "                                                 ║\n"
        "                                                 ║\n"
        "                                                 ║     "   COLOR_DEFAULT "Manila" COLOR_BLUE    "       ╔╗                    "                                    "╔╗\n"
        "                                                 ╚═══════" COLOR_DEFAULT   "◯"    COLOR_BLUE "══════════╝║       "    COLOR_DEFAULT "Pandakan" COLOR_BLUE     "     ║╚═══════╗\n"
        "                                                         " COLOR_DEFAULT   "↑"    COLOR_BLUE "           ╚══════════" COLOR_DEFAULT    "◯"     COLOR_BLUE "═════════╝       ╔╝    " COLOR_DEFAULT "Sapa" COLOR_BLUE "\n"
        "                                                                                                  "                                                                        "╚══════" COLOR_DEFAULT "◯\n");
            // clang-format on

            break;

        case 'M':
            // clang-format off
      printf(
        "                                               Tondo\n"
        "                                                 ◯\n" COLOR_BLUE
        "                                                 ║\n"
        "                                                 ║\n"
        "                                                 ║     "   COLOR_DEFAULT "Manila" COLOR_BLUE       "       ╔╗                    "                                    "╔╗\n"
        "                                                 ╚═══════" COLOR_DEFAULT   "◯"    COLOR_BLUE    "══════════╝║       "    COLOR_DEFAULT "Pandakan" COLOR_BLUE     "     ║╚═══════╗\n"
        "                                                         " COLOR_DEFAULT   "↑"    COLOR_BLUE    "           ╚══════════" COLOR_DEFAULT    "◯"     COLOR_BLUE "═════════╝       ╔╝    " COLOR_DEFAULT "Sapa\n"
        "                                                   "                 "You are here!" COLOR_BLUE "                                  "                                          "╚══════" COLOR_DEFAULT "◯\n");
            // clang-format on

            break;

        case 'P':
            // clang-format off
      printf(
        "                                               Tondo\n"
        "                                                 ◯\n" COLOR_BLUE
        "                                                 ║\n"
        "                                                 ║\n"
        "                                                 ║     "   COLOR_DEFAULT "Manila" COLOR_BLUE    "       ╔╗                    "                                    "╔╗\n"
        "                                                 ╚═══════" COLOR_DEFAULT   "◯"    COLOR_BLUE "══════════╝║       "    COLOR_DEFAULT "Pandakan" COLOR_BLUE     "     ║╚═══════╗\n"
        "                                                         " COLOR_DEFAULT   "↑"    COLOR_BLUE "           ╚══════════" COLOR_DEFAULT    "◯"     COLOR_BLUE "═════════╝       ╔╝    " COLOR_DEFAULT "Sapa" COLOR_BLUE "\n"
        "                                                                                "                                                      "↑"     COLOR_BLUE "                 ╚══════" COLOR_DEFAULT "◯\n"
        "                                                                          "                                                      "You are here!\n");
            // clang-format on

            break;

        case 'S':
            // clang-format off
      printf(
        "                                               Tondo\n"
        "                                                 ◯\n" COLOR_BLUE
        "                                                 ║\n"
        "                                                 ║\n"
        "                                                 ║     "   COLOR_DEFAULT "Manila" COLOR_BLUE    "       ╔╗                    "                                    "╔╗\n"
        "                                                 ╚═══════" COLOR_DEFAULT   "◯"    COLOR_BLUE "══════════╝║       "    COLOR_DEFAULT "Pandakan" COLOR_BLUE     "     ║╚═══════╗\n"
        "                                                         " COLOR_DEFAULT   "↑"    COLOR_BLUE "           ╚══════════" COLOR_DEFAULT    "◯"     COLOR_BLUE "═════════╝       ╔╝    " COLOR_DEFAULT "Sapa" COLOR_BLUE "\n"
        "                                                                                                  "                                                                        "╚══════" COLOR_DEFAULT "◯\n"
        "                                                                                                         "                                                                                         "↑\n"
        "                                                                                                   "                                                                                         "You are here!\n");
            // clang-format on

            break;
    }

    printf("\n\n\n");
}

/**
 * @brief Prints out the game's navigation screen, which contains the new port the player navigated
 * to and the new day count, to the console.
 * @param bIsSuccessful Whether or not the departure was successful.
 * @param cPortId The ID of the port.
 * @param nPlayerTurns The number of turns the player has exhausted.
 * @pre @p bIsSuccessful must have an integer value of either `0` or `1`.
 * @pre @p cPortId must have a character value of `T`, `M`, `P`, or `S`.
 * @pre @p nPlayerTurns must have a a two-digit positive integer value.
 */
void printNavigationScreen(int bIsSuccessful, char cPortId, int nPlayerTurns) {
    printSeparator();

    if (bIsSuccessful) {
        printf(
            "                                               ▗▄▄▄ ▗▄▄▄▖▗▄▄▖  ▗▄▖ ▗▄▄▖▗▄▄▄▖▗▄▄▄▖▗▄▄▄     ▗▄▄▖  ▗▄▖ ▗▄▄▖▗▄▄▄▖\n"
            "                                               ▐▌  █▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌ █  ▐▌   ▐▌  █    ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌ █\n"
            "                                               ▐▌  █▐▛▀▀▘▐▛▀▘ ▐▛▀▜▌▐▛▀▚▖ █  ▐▛▀▀▘▐▌  █    ▐▛▀▘ ▐▌ ▐▌▐▛▀▚▖ █\n"
            "                                               ▐▙▄▄▀▐▙▄▄▖▐▌   ▐▌ ▐▌▐▌ ▐▌ █  ▐▙▄▄▖▐▙▄▄▀    ▐▌   ▝▚▄▞▘▐▌ ▐▌ █\n");

        printf("\n\n");

        setConsoleColorToGreen();

        switch (cPortId) {
            case 'T':
                printf("%*cYou have navigated to the port of Tondo!\n", 58, ' ');

                break;

            case 'M':
                printf("%*cYou have navigated to the port of Manila!\n", 57, ' ');

                break;

            case 'P':
                printf("%*cYou have navigated to the port of Pandakan!\n", 56, ' ');

                break;

            case 'S':
                printf("%*cYou have navigated to the port of Sapa!\n", 58, ' ');

                break;
        }
    } else {
        printf(
            "                               ▗▄▄▄ ▗▄▄▄▖▗▄▄▖  ▗▄▖ ▗▄▄▖▗▄▄▄▖▗▖ ▗▖▗▄▄▖ ▗▄▄▄▖    ▗▄▄▖  ▗▄▖  ▗▄▄▖▗▄▄▄▖▗▄▄▖  ▗▄▖ ▗▖  ▗▖▗▄▄▄▖▗▄▄▄ \n"
            "                               ▐▌  █▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌ █  ▐▌ ▐▌▐▌ ▐▌▐▌       ▐▌ ▐▌▐▌ ▐▌▐▌     █  ▐▌ ▐▌▐▌ ▐▌▐▛▚▖▐▌▐▌   ▐▌  █\n"
            "                               ▐▌  █▐▛▀▀▘▐▛▀▘ ▐▛▀▜▌▐▛▀▚▖ █  ▐▌ ▐▌▐▛▀▚▖▐▛▀▀▘    ▐▛▀▘ ▐▌ ▐▌ ▝▀▚▖  █  ▐▛▀▘ ▐▌ ▐▌▐▌ ▝▜▌▐▛▀▀▘▐▌  █\n"
            "                               ▐▙▄▄▀▐▙▄▄▖▐▌   ▐▌ ▐▌▐▌ ▐▌ █  ▝▚▄▞▘▐▌ ▐▌▐▙▄▄▖    ▐▌   ▝▚▄▞▘▗▄▄▞▘  █  ▐▌   ▝▚▄▞▘▐▌  ▐▌▐▙▄▄▖▐▙▄▄▀\n");

        printf("\n\n");

        setConsoleColorToRed();

        switch (cPortId) {
            case 'T':
                printf("%*cYou could not depart for the port of Tondo due to the weather.\n", 47,
                       ' ');

                break;

            case 'M':
                printf("%*cYou could not depart for the port of Manila due to the weather.\n", 46,
                       ' ');

                break;

            case 'P':
                printf("%*cYou could not depart for the port of Pandakan due to the weather.\n", 45,
                       ' ');

                break;

            case 'S':
                printf("%*cYou could not depart for the port of Sapa due to the weather.\n", 47,
                       ' ');

                break;
        }
    }

    resetConsoleColor();

    printf("\n");

    printf("%*cDay %2d → %2d", 72, ' ', nPlayerTurns, nPlayerTurns + 1);

    printf("\n\n\n\n\n");
}

/**
 * @brief Prints out the game's weather report screen, which contains details about the storm and
 * the applied debuffs, to the console.
 * @param bIsNewStorm Whether or not the storm is new.
 * @param nStormOldWindSignalNumber The storm's old wind signal number.
 * @param nStormNewWindSignalNumber The storm's new wind signal number.
 * @param nPostponedDepartureChance The percentage chance of the player being unable to depart their
 * current port.
 * @param nStormTurnDuration The turn duration of the storm.
 * @pre @p bIsNewStorm must have an integer value of either `0` or `1`.
 */
void printWeatherReportScreen(int bIsNewStorm, int nStormOldWindSignalNumber,
                              int nStormNewWindSignalNumber, int nPostponedDepartureChance,
                              int nStormTurnDuration) {
    printSeparator();

    setConsoleColorToBlue();
    printf(
        "                                            ▗▖ ▗▖▗▄▄▄▖ ▗▄▖▗▄▄▄▖▗▖ ▗▖▗▄▄▄▖▗▄▄▖     ▗▄▄▖ ▗▄▄▄▖▗▄▄▖  ▗▄▖ ▗▄▄▖▗▄▄▄▖\n"
        "                                            ▐▌ ▐▌▐▌   ▐▌ ▐▌ █  ▐▌ ▐▌▐▌   ▐▌ ▐▌    ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌ █\n"
        "                                            ▐▌ ▐▌▐▛▀▀▘▐▛▀▜▌ █  ▐▛▀▜▌▐▛▀▀▘▐▛▀▚▖    ▐▛▀▚▖▐▛▀▀▘▐▛▀▘ ▐▌ ▐▌▐▛▀▚▖ █\n"
        "                                            ▐▙█▟▌▐▙▄▄▖▐▌ ▐▌ █  ▐▌ ▐▌▐▙▄▄▖▐▌ ▐▌    ▐▌ ▐▌▐▙▄▄▖▐▌   ▝▚▄▞▘▐▌ ▐▌ █\n");
    resetConsoleColor();

    printf("\n\n");

    if (nStormTurnDuration > 0) {
        if (bIsNewStorm) {
            setConsoleColorToRed();
            printf("%*cA new storm has formed.\n", 66, ' ');
            resetConsoleColor();

            printf("\n");
        }

        if (nStormOldWindSignalNumber != nStormNewWindSignalNumber) {
            printf("%*cWind Signal Number %d → %d", 66, ' ', nStormOldWindSignalNumber,
                   nStormNewWindSignalNumber);
        } else {
            printf("%*cWind Signal Number %d", 68, ' ', nStormNewWindSignalNumber);
        }

        printf("\n");

        if (nStormNewWindSignalNumber == 1) {
            printf(
                "                                          .----------------.\n"
                "                                         | .--------------. |\n"
                "                                         | |     __       | |\n"
                "                                         | |    /  |      | |\n"
                "                                         | |    `| |      | |        Tropical Depression (TD)\n"
                "                                         | |     | |      | |        <= 61 km/h\n"
                "                                         | |    _| |_     | |        Minimal to minor threat to life and property.\n"
                "                                         | |   |_____|    | |\n"
                "                                         | |              | |\n"
                "                                         | '--------------' |\n"
                "                                          '----------------'\n");
        } else if (nStormNewWindSignalNumber == 2) {
            setConsoleColorToCyan();
            printf(
                "                                          .----------------.\n"
                "                                         | .--------------. |\n"
                "                                         | |    _____     | |\n"
                "                                         | |   / ___ `.   | |\n"
                "                                         | |  |_/___) |   | |        Tropical Storm (TS)\n"
                "                                         | |   .'____.'   | |        62 - 88 km/h\n"
                "                                         | |  / /____     | |        Minor to moderate threat to life and property.\n"
                "                                         | |  |_______|   | |\n"
                "                                         | |              | |\n"
                "                                         | '--------------' |\n"
                "                                          '----------------'\n");
        } else if (nStormNewWindSignalNumber == 3) {
            setConsoleColorToYellow();
            printf(
                "                                       .----------------.\n"
                "                                      | .--------------. |\n"
                "                                      | |    ______    | |\n"
                "                                      | |   / ____ `.  | |\n"
                "                                      | |   `'  __) |  | |        Severe Tropical Storm (STS)\n"
                "                                      | |   _  |__ '.  | |        89 - 117 km/h\n"
                "                                      | |  | \\____) |  | |        Moderate to significant threat to life and property.\n"
                "                                      | |   \\______.'  | |\n"
                "                                      | |              | |\n"
                "                                      | '--------------' |\n"
                "                                       '----------------'\n");
        } else if (nStormNewWindSignalNumber == 4) {
            setConsoleColorToRed();
            printf(
                "                                        .----------------.\n"
                "                                       | .--------------. |\n"
                "                                       | |   _    _     | |\n"
                "                                       | |  | |  | |    | |\n"
                "                                       | |  | |__| |_   | |        Typhoon (TY)\n"
                "                                       | |  |____   _|  | |        118 - 184 km/h\n"
                "                                       | |      _| |_   | |        Significant to severe threat to life and property.\n"
                "                                       | |     |_____|  | |\n"
                "                                       | |              | |\n"
                "                                       | '--------------' |\n"
                "                                        '----------------'\n");
        } else {
            setConsoleColorToPurple();
            printf(
                "                                               .----------------.\n"
                "                                              | .--------------. |\n"
                "                                              | |   _______    | |\n"
                "                                              | |  |  _____|   | |\n"
                "                                              | |  | |____     | |        Super Typhoon (STY)\n"
                "                                              | |  '_.____''.  | |        >= 185 km/h\n"
                "                                              | |  | \\____) |  | |        Extreme threat to life and property.\n"
                "                                              | |   \\______.'  | |\n"
                "                                              | |              | |\n"
                "                                              | '--------------' |\n"
                "                                               '----------------'\n");
        }

        if (nStormNewWindSignalNumber > 1) {
            resetConsoleColor();
        }

        printf("\n\n");

        int nConsoleLeftPaddingSize = 44;

        if (nStormNewWindSignalNumber > 2) {
            setConsoleColorToRed();
            printf("%*c• The chances of a postponed departure are %d%%.\n", nConsoleLeftPaddingSize,
                   ' ', nPostponedDepartureChance);
            resetConsoleColor();
        }

        printf("%*c• The storm will last for %d more day/s.", nConsoleLeftPaddingSize, ' ',
               nStormTurnDuration);
    } else {
        setConsoleColorToGreen();
        printf("%*cThe storm has left the area of responsibility!\n", 55, ' ');
        resetConsoleColor();
    }

    printf("\n\n\n\n\n");
}

/**
 * @brief Prints out the game's end screen, which contains the player's final statistics, to the
 * console.
 * @param nPlayerFinalProfit The player's final profit percentage.
 * @param nPlayerProfitTarget The player's target profit percentage.
 * @param nPlayerFinalBalance The player's final gold coin balance.
 * @param nPlayerInitialBalance The player's inital gold coin balance.
 * @param nPlayerFinalTurns The number of turns the player has exhausted.
 */
void printGameEndScreen(int nPlayerFinalProfit, int nPlayerProfitTarget, int nPlayerFinalBalance,
                        int nPlayerInitialBalance, int nPlayerFinalTurns) {
    printSeparator();

    int nConsoleLeftPaddingSize;

    if (nPlayerFinalProfit >= nPlayerProfitTarget) {
        setConsoleColorToYellow();
        printf(
            "                                              ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗██╗\n"
            "                                              ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║██║\n"
            "                                               ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║██║\n"
            "                                                ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║╚═╝\n"
            "                                                 ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║██╗\n"
            "                                                 ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝\n");

        printf("\n");

        printf(
            "                                                                       ___________\n"
            "                                                                      '._==_==_=_.'\n"
            "                                                                      .-\\:      /-.\n"
            "                                                                      | (|:.    ) |\n"
            "                                                                      '-|:.     |-'\n"
            "                                                                        \\::.    /\n"
            "                                                                         '::. .'\n"
            "                                                                           ) (\n"
            "                                                                         _.' '._\n"
            "                                                                        `\"\"\"\"\"\"\"`\n");
        resetConsoleColor();

        printf("\n\n");

        nConsoleLeftPaddingSize = 46;
    } else {
        setConsoleColorToRed();
        printf(
            "                                            ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗      ██████╗ ███████╗████████╗██╗\n"
            "                                            ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║     ██╔═══██╗██╔════╝╚══██╔══╝██║\n"
            "                                             ╚████╔╝ ██║   ██║██║   ██║    ██║     ██║   ██║███████╗   ██║   ██║\n"
            "                                              ╚██╔╝  ██║   ██║██║   ██║    ██║     ██║   ██║╚════██║   ██║   ╚═╝\n"
            "                                               ██║   ╚██████╔╝╚██████╔╝    ███████╗╚██████╔╝███████║   ██║   ██╗\n"
            "                                               ╚═╝    ╚═════╝  ╚═════╝     ╚══════╝ ╚═════╝ ╚══════╝   ╚═╝   ╚═╝\n");
        resetConsoleColor();

        printf("\n\n");

        nConsoleLeftPaddingSize = 44;
    }

    printf("%*c• Final profit made:", nConsoleLeftPaddingSize, ' ');

    if (nPlayerFinalProfit >= nPlayerProfitTarget) {
        setConsoleColorToGreen();
    } else {
        setConsoleColorToRed();
    }

    printf(" %d%% (%d gold coins)\n", nPlayerFinalProfit,
           nPlayerFinalBalance - nPlayerInitialBalance);
    resetConsoleColor();

    printf("%*c• Number of turns (days) exhausted: %d\n", nConsoleLeftPaddingSize, ' ',
           nPlayerFinalTurns);

    printf("\n\n\n");
}
