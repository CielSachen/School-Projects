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

#include "weather.h"

#include <stdlib.h>

/**
 * @brief Generates a random boolean based on the passed chance of returning a `true`.
 * @param nTruePercentChance The percentage chance of this function returning `1`.
 * @pre @p nTruePercentChance must have a positive integer value greater than or equal to  `1` and less than or equal to
 * `100`.
 * @return `1` if `true` or `0` if `false`.
 */
int generateRandomBool(int nTruePercentChance) { return (rand() % 100) + 1 <= nTruePercentChance; }

/**
 * @brief Generates a random duration in turns for a storm within the passed minimum and constant maximum turn duration.
 * @param nMinimumTurnDuration The minimum allowed duration in turns.
 * @return An integer value within the range of `nMinimumTurnDuration` and `10`.
 */
int generateRandomStormTurnDuration(int nMinimumTurnDuration) {
  return (rand() % (MAXIMUM_STORM_TURN_DURATION - nMinimumTurnDuration + 1)) + nMinimumTurnDuration;
}

/**
 * @brief Sets the wind signal number of the storm to the given new wind signal number and sets its debuffs.
 * @param[in,out] nStormCurrentWindSignalNumber The storm's current wind signal number.
 * @param nStormNewWindSignalNumber The storm's new wind signal number.
 * @param[out] nPostponedDepartureChance The percentage chance of the player being unable to depart their current port.
 */
void setStormStrength(int* nStormCurrentWindSignalNumber, int nStormNewWindSignalNumber,
                      int* nPostponedDepartureChance) {
  *nStormCurrentWindSignalNumber = nStormNewWindSignalNumber;

  if (*nStormCurrentWindSignalNumber < 3) {
    *nPostponedDepartureChance = DEFAULT_POSTPONED_DEPARTURE_CHANCE;
  } else if (*nStormCurrentWindSignalNumber == 3) {
    *nPostponedDepartureChance = SIGNAL_THREE_STORM_POSTPONED_DEPARTURE_CHANCE;
  } else if (*nStormCurrentWindSignalNumber == 4) {
    *nPostponedDepartureChance = SIGNAL_FOUR_STORM_POSTPONED_DEPARTURE_CHANCE;
  } else {
    *nPostponedDepartureChance = SIGNAL_FIVE_STORM_POSTPONED_DEPARTURE_CHANCE;
  }
}
