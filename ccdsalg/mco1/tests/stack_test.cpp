extern "C" {
#include "convex_hull/stack.h"
}

#include <gtest/gtest.h>

TEST(Create, SetsLengthToNegativeOne) {
    Stack stack;

    create(&stack);

    EXPECT_EQ(stack.length, 0);
}

TEST(Push, AddsElementToEndOfArray) {
    Stack stack;

    create(&stack);

    Point elm = {0, 0};

    push(&stack, elm);

    const Point *const inserted_elm = &stack.data[0];

    EXPECT_EQ(inserted_elm->x, elm.x);
    EXPECT_EQ(inserted_elm->y, elm.y);
}

TEST(Push, IncreasesLength) {
    Stack stack;

    create(&stack);

    Point elm = {0, 0};

    push(&stack, elm);

    EXPECT_EQ(stack.length, 1);
}

TEST(Pop, ReturnsLastElement) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_elm = {1, 1};

    push(&stack, last_elm);

    const Point popped_elm = pop(&stack);

    EXPECT_EQ(popped_elm.x, last_elm.x);
    EXPECT_EQ(popped_elm.y, last_elm.y);
}

TEST(Pop, DecreasesLength) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_elm = {1, 1};

    push(&stack, last_elm);

    pop(&stack);

    EXPECT_EQ(stack.length, 1);
}

TEST(Top, ReturnsLastElement) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_elm = {1, 1};

    push(&stack, last_elm);

    const Point *const top_element = top(&stack);

    EXPECT_EQ(top_element->x, last_elm.x);
    EXPECT_EQ(top_element->y, last_elm.y);
}

TEST(Top, DoesNotMutateLength) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    Point last_elm = {1, 1};

    push(&stack, last_elm);

    top(&stack);

    EXPECT_EQ(stack.length, 2);
}

TEST(IsFull, ReturnsTrueIfLengthIsMax) {
    Stack stack;

    create(&stack);

    for (std::size_t i = 0; i < MAX_STACK_LENGTH; i++) {
        push(&stack, {0, 0});
    }

    EXPECT_TRUE(is_full(&stack));
}

TEST(IsFull, ReturnsFalseIfLengthIsNotMax) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    EXPECT_FALSE(is_full(&stack));
}

TEST(IsEmpty, ReturnsTrueIfLengthIsZero) {
    Stack stack;

    create(&stack);

    EXPECT_TRUE(is_empty(&stack));
}

TEST(IsEmpty, ReturnsFalseIfLengthIsNotZero) {
    Stack stack;

    create(&stack);

    push(&stack, {0, 0});

    EXPECT_FALSE(is_empty(&stack));
}
