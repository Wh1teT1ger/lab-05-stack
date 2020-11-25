// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include <Stack.hpp>

TEST(Stack, constructor){
  Stack<int> stack;
  EXPECT_EQ(stack.size(), 0);
  stack.push(1);
  EXPECT_EQ(stack.size(), 1);
}

TEST(Stack, push_rvalue){
  Stack<int> stack;
  stack.push(1);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 1);
  stack.push(2);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), 2);
}

TEST(Stack, push_lvalue){
  int value = 2;
  Stack<int> stack;
  stack.push(value);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 2);
  value = 3;
  stack.push(value);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), 3);
}

TEST(Stack, push_emplace){
  Stack<std::string> stack;
  stack.push_emplace(3, 't');
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), "ttt");
  stack.push_emplace("hello");
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), "hello");
}

TEST(Stack, pop){
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), 2);
  stack.pop();
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 1);
  stack.pop();
  EXPECT_EQ(stack.size(), 0);
}