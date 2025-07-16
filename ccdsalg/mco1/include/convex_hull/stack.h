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
 * @brief The header containing the public APIs of the stack and its helper functions.
 * @copyright GNU AGPLv3
 */

#ifndef CONVEX_HULL_STACK_H_
#define CONVEX_HULL_STACK_H_

#include <stdbool.h>
#include <stddef.h>

#include "geometry.h"

/** @brief The maximum number of elements a stack can contain. */
#define MAX_STACK_LENGTH 32768

/**
 * @brief A collection implementing a [stack data structure](https://www.geeksforgeeks.org/dsa/stack-data-structure/)
 * using an array.
 */
typedef struct Stack {
    /** @brief The ordered data being contained by the stack. */
    Point data[MAX_STACK_LENGTH];
    /** @brief The number of elements contained by the stack. */
    size_t length;
} Stack;

/**
 * @brief Initializes a stack’s top index to its default value.
 * @param[in,out] stack The stack to initialize.
 */
void create(Stack *const stack);

/**
 * @brief Adds an element into the top of a stack.
 * @param[in,out] stack The stack to add to.
 * @param element The element to add.
 */
void push(Stack *const stack, const Point element);

/**
 * @brief Removes the element at the top of a stack.
 * @param[in] stack The stack to remove from.
 * @return The element removed from the stack.
 */
Point pop(Stack *const stack);

/**
 * @brief Gets the element at the top of a stack.
 * @param[in] stack The stack to get from.
 * @return A pointer to the element at the top of the stack.
 */
Point *top(Stack *const stack);

/**
 * @brief Checks if a stack contains the maximum number of elements.
 * @param[in] stack The stack to check.
 * @return Whether the stack’s top index is `MAX_STACK_LENGTH`.
 */
bool is_full(const Stack *const stack);

/**
 * @brief Checks if a stack contains no elements.
 * @param[in] stack The stack to check.
 * @return Whether the stack’s top index is `-1`.
 */
bool is_empty(const Stack *const stack);

#endif  // CONVEX_HULL_STACK_H_
