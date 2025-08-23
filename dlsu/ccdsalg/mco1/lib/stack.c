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

#include "convex_hull/stack.h"

#include <stdint.h>

/**
 * @brief Initializes a stack's elements and top index to their default values.
 * @details This sets the stack's top index to `SIZE_MAX`.
 * @relates Stack
 * @param[in,out] stack The stack to initialize.
 */
void create(Stack* const stack) { stack->top = SIZE_MAX; }

/**
 * @brief Adds an element into the top of a stack.
 * @details This increments the stack's top index and assigns the element to that index, even if the stack is full.
 * @relates Stack
 * @param[in,out] stack The stack to add to.
 * @param elm The element to add.
 * @pre The stack is not full.
 */
void push(Stack* const stack, const Point elm) { stack->elements[++stack->top] = elm; }

/**
 * @brief Removes the element at the top of a stack.
 * @details This decrements the stack's top index, even if it's empty.
 * @relates Stack
 * @param[in,out] stack The stack to remove from.
 * @return The element removed from the stack.
 * @pre The stack is not empty.
 */
Point pop(Stack* const stack) { return stack->elements[stack->top--]; }

/**
 * @brief Gets the element at the top of a stack.
 * @relates Stack
 * @param[in] stack The stack to get from.
 * @return A pointer to the element at the top of the stack, or `NULL` if the stack is empty.
 */
const Point* top(Stack* const stack) {
  if (is_empty(stack)) {
    return NULL;
  }

  return &stack->elements[stack->top];
}

/**
 * @brief Gets the element second from the top of the stack.
 * @relates Stack
 * @param[in] stack The stack to get from.
 * @return A pointer to the element second from the top of the stack, or `NULL` if the stack is empty.
 */
const Point* next_to_top(Stack* const stack) {
  if (is_empty(stack) || stack->top == 0) {
    return NULL;
  }

  return &stack->elements[stack->top - 1];
}

/**
 * @brief Checks if a stack contains the maximum number of elements.
 * @details This checks if the stack's top index is one less than `MAX_STACK_SIZE` (`MAX_STACK_SIZE - 1`).
 * @relates Stack
 * @param[in] stack The stack to check.
 * @return Whether the stack contains the maximum number of elements.
 */
bool is_full(const Stack* const stack) { return stack->top == MAX_STACK_SIZE - 1; }

/**
 * @brief Checks if a stack contains no elements.
 * @details This checks if the stack's top index is `SIZE_MAX`.
 * @relates Stack
 * @param[in] stack The stack to check.
 * @return Whether the stack contains no elements.
 */
bool is_empty(const Stack* const stack) { return stack->top == SIZE_MAX; }
