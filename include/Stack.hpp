// Copyright 2020 Burylov Denis <burylov01@mail.ru>

#ifndef INCLUDE__STACK_HPP
#define INCLUDE__STACK_HPP

#include <cstddef>
#include <utility>

template <typename T>
class Stack {
  struct Node {
    T value;
    Node* _prev;
  };
  size_t _size;
  Node* _heap;

 public:
  Stack();
  ~Stack();
  Stack(const Stack&) = delete;
  Stack& operator=(const Stack&) = delete;
  Stack(Stack&& stack) noexcept;
  Stack& operator=(Stack&& stack) noexcept;

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  template <typename... Args>
  void push_emplace(Args&&... value);
  size_t size() const;
};

template <typename T>
Stack<T>::Stack() : _size(0), _heap(nullptr) {}

template <typename T>
Stack<T>::~Stack() {
  auto top = _heap;
  while (top != nullptr) {
    auto prev = top->_prev;
    delete top;
    top = prev;
  }
}

template <typename T>
Stack<T>::Stack(Stack<T>&& stack) noexcept {
  _size = std::move(stack._size);
  _heap = std::move(stack._heap);
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& stack) noexcept {
  std::swap(_size, stack._size);
  std::swap(_heap, stack._heap);
  return *this;
}

template <typename T>
void Stack<T>::push(T&& value) {
  _heap = new Node{std::move(value), _heap};
  _size++;
}

template <typename T>
void Stack<T>::push(const T& value) {
  _heap = new Node{value, _heap};
  _size++;
}

template <typename T>
void Stack<T>::pop() {
  auto heap = _heap;
  if (heap == nullptr) return;
  auto new_heap = _heap->_prev;
  if (new_heap == nullptr) {
    _heap = nullptr;
    _size = 0;
  } else {
    _heap = new_heap;
    _size--;
  }
  delete heap;
}

template <typename T>
const T& Stack<T>::head() const {
  return _heap->value;
}

template <typename T>
template <typename... Args>
void Stack<T>::push_emplace(Args&&... value) {
  _heap = new Node{T(std::forward<Args>(value)...), _heap};
  _size++;
}

template <typename T>
size_t Stack<T>::size() const {
  return _size;
}

#endif  // INCLUDE__STACK_HPP
