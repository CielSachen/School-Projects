/*
 * Convex Hull finds the convex hull from a set of points on a Cartesian plane.
 * Copyright (C) 2025  Raphael Panaligan  Jek Degullado
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

/**
 * @file stack.h
 * @brief The public APIs of the stack implementation and its helper functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONVEX_HULL_STACK_H_
#define CONVEX_HULL_STACK_H_

#include <stdbool.h>
#include <stddef.h>

#include "geometry.h"

/** @brief The maximum number of elements a stack can contain. */
#define MAX_STACK_SIZE 32768

/**
 * @brief A collection implementing the [stack data structure](https://www.geeksforgeeks.org/dsa/stack-data-structure/)
 * using an array.
 */
typedef struct Stack {
  /**
   * @brief The ordered elements contained in the stack.
   * @private
   */
  Point elements[MAX_STACK_SIZE];
  /**
   * @brief The index of the element at the top of the stack.
   * @private
   */
  size_t top;
} Stack;

/**
 * @brief Initializes a stack's elements and top index to their default values.
 * @details This sets the stack's top index to `SIZE_MAX`.
 * @relates Stack
 * @param[in,out] stack The stack to initialize.
 */
void create(Stack* const stack);

/**
 * @brief Adds an element into the top of a stack.
 * @details This increments the stack's top index and assigns the element to that index, even if the stack is full.
 * @relates Stack
 * @param[in,out] stack The stack to add to.
 * @param element The element to add.
 * @pre The stack is not full.
 */
void push(Stack* const stack, Point element);

/**
 * @brief Removes the element at the top of a stack.
 * @details This decrements the stack's top index, even if it's empty.
 * @relates Stack
 * @param[in,out] stack The stack to remove from.
 * @return The element removed from the stack.
 * @pre The stack is not empty.
 */
Point pop(Stack* const stack);

/**
 * @brief Gets the element at the top of a stack.
 * @relates Stack
 * @param[in] stack The stack to get from.
 * @return A pointer to the element at the top of the stack, or `NULL` if the stack is empty.
 */
const Point* top(Stack* const stack);

/**
 * @brief Gets the element second from the top of the stack.
 * @relates Stack
 * @param[in] stack The stack to get from.
 * @return A pointer to the element second from the top of the stack, or `NULL` if the stack is empty.
 */
const Point* next_to_top(Stack* const stack);

/**
 * @brief Checks if a stack contains the maximum number of elements.
 * @details This checks if the stack's top index is one less than `MAX_STACK_SIZE` (`MAX_STACK_SIZE - 1`).
 * @relates Stack
 * @param[in] stack The stack to check.
 * @return Whether the stack contains the maximum number of elements.
 */
bool is_full(const Stack* const stack);

/**
 * @brief Checks if a stack contains no elements.
 * @details This checks if the stack's top index is `SIZE_MAX`.
 * @relates Stack
 * @param[in] stack The stack to check.
 * @return Whether the stack contains no elements.
 */
bool is_empty(const Stack* const stack);

#endif  // CONVEX_HULL_STACK_H_

#ifdef __cplusplus
}
#endif
