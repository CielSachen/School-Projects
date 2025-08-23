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

#include "social_network/queue.h"

#include <stdint.h>
#include <string.h>

/**
 * @brief Initializes a queue's elements and indexes to their default values.
 * @details This sets the queue's front index to `SIZE_MAX` and rear index to zero.
 * @relates Queue
 * @param[in,out] queue The queue to initialize.
 */
void initialize_queue(Queue* const queue) {
  queue->front = SIZE_MAX;
  queue->rear = 0;
}

/**
 * @brief Adds an element to the rear of the queue.
 * @details This assigns the element to the queue's rear index and increments the index, even if the queue is full.
 * @relates Queue
 * @param[in,out] queue The queue to add to.
 * @param[in] elm The element to add.
 * @pre The queue is not full.
 */
void enqueue(Queue* const queue, const Vertex elm) { strncpy(queue->elements[queue->rear++], elm, MAX_GRAPH_ORDER); }

/**
 * @brief Removes the element at the front of the queue.
 * @details This increments the queue's front index if it's not empty. Otherwise, this will do nothing.
 * @relates Queue
 * @param[in,out] queue The queue to remove from.
 */
void dequeue(Queue* const queue) {
  if (is_empty(queue)) {
    return;
  }

  queue->front++;
}

/**
 * @brief Gets the element at the front of the queue.
 * @relates Queue
 * @param[in] queue The queue to get from.
 * @param[out] elm The element at the front of the queue, or an empty string if the queue is empty.
 */
void peak(Queue* const queue, Vertex elm) {
  if (is_empty(queue)) {
    for (size_t i = 0; i < MAX_VERTEX_LABEL_LENGTH; i++) {
      elm[i] = '\0';
    }

    return;
  }

  strncpy(elm, queue->elements[queue->front + 1], MAX_VERTEX_LABEL_LENGTH);
}

/**
 * @brief Checks if a queue contains the maximum number of elements.
 * @details This checks if the queue's rear index is `MAX_QUEUE_SIZE`.
 * @relates Queue
 * @param[in] queue The queue to check.
 * @return Whether the queue contains the maximum number of elements.
 */
bool is_full(const Queue* const queue) { return queue->rear == MAX_QUEUE_SIZE; }

/**
 * @brief Checks if a queue contains contains no queueing elements.
 * @details This checks if the queue's front index is one less than its rear index (`queue->rear - 1`).
 * @relates Queue
 * @param[in] queue The queue to check.
 * @return Whether the queue contains contains no queueing elements.
 */
bool is_empty(const Queue* const queue) { return queue->front == queue->rear - 1; }
