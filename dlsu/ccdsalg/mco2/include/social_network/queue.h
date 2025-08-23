/*
 * Social Network processes a graph for its details and traversal sequences.
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
 * @file queue.h
 * @brief The public APIs of the queue implementation and its helper functions.
 * @author Raphael Panaligan
 * @author Jek Degullado
 * @copyright GNU AGPLv3
 */

#ifndef SOCIAL_NETWORK_QUEUE_H_
#define SOCIAL_NETWORK_QUEUE_H_

#include <stddef.h>

#include "graph.h"

/**
 * @brief The maximum number of elements a queue can contain.
 * @details The queue uses a simple implementation. Therefore, this will include removed elements as well.
 */
#define MAX_QUEUE_SIZE (MAX_GRAPH_ORDER * MAX_GRAPH_ORDER)

/**
 * @brief A collection implementing the [queue data structure](https://www.geeksforgeeks.org/dsa/queue-data-structure/)
 * using an array.
 * @details This is a simple implementation, not a circular implementation. Therefore, the queue can only be consumed
 * once.
 */
typedef struct Queue {
  /**
   * @brief The ordered elements contained in the queue.
   * @private
   */
  Vertex elements[MAX_QUEUE_SIZE];
  /**
   * @brief The index of the first element in the queue.
   * @private
   */
  size_t front;
  /**
   * @brief The index of the last element in the queue.
   * @private
   */
  size_t rear;
} Queue;

/**
 * @brief Initializes a queue's elements and indexes to their default values.
 * @details This sets the queue's front index to `SIZE_MAX` and rear index to zero.
 * @relates Queue
 * @param[in,out] queue The queue to initialize.
 */
void initialize_queue(Queue* const queue);

/**
 * @brief Adds an element to the rear of the queue.
 * @details This assigns the element to the queue's rear index and increments the index, even if the queue is full.
 * @relates Queue
 * @param[in,out] queue The queue to add to.
 * @param[in] element The element to add.
 * @pre The queue is not full.
 */
void enqueue(Queue* const queue, const Vertex element);

/**
 * @brief Removes the element at the front of the queue.
 * @details This increments the queue's front index if it's not empty. Otherwise, this will do nothing.
 * @relates Queue
 * @param[in,out] queue The queue to remove from.
 */
void dequeue(Queue* const queue);

/**
 * @brief Gets the element at the front of the queue.
 * @relates Queue
 * @param[in] queue The queue to get from.
 * @param[out] element The element at the front of the queue, or an empty string if the queue is empty.
 */
void peak(Queue* const queue, Vertex element);

/**
 * @brief Checks if a queue contains the maximum number of elements.
 * @details This checks if the queue's rear index is `MAX_QUEUE_SIZE`.
 * @relates Queue
 * @param[in] queue The queue to check.
 * @return Whether the queue contains the maximum number of elements.
 */
bool is_full(const Queue* const queue);

/**
 * @brief Checks if a queue contains contains no queueing elements.
 * @details This checks if the queue's front index is one less than its rear index (`queue->rear - 1`).
 * @relates Queue
 * @param[in] queue The queue to check.
 * @return Whether the queue contains contains no queueing elements.
 */
bool is_empty(const Queue* const queue);

#endif  // SOCIAL_NETWORK_QUEUE_H_
