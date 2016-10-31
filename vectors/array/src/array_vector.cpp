#include <iostream>
#include <cstring>
#include <stdexcept>

#include "array_vector.h"

int array_vector::size() const {
  return _size;
}

int array_vector::capacity() const {
  return _capacity;
}

bool array_vector::is_empty() const {
  return _size == 0;
}

int array_vector::at(int i) const {
  return _data[i];
}

void array_vector::push(int value) {
  if (_size >= _capacity) {
    _resize(_capacity * 2);
  }
  _data[_size++] = value;
}

void array_vector::_resize(int new_capacity) {
  if (new_capacity < MIN_CAPACITY) {
    return;
  }
  int *new_data = new int[new_capacity];

  std::memmove(new_data, _data, _size * sizeof(int));

  _capacity = new_capacity;
  int *old_data = _data;
  _data = new_data;

  delete[] old_data;
}

int array_vector::pop() {
  if (_size == 0) {
    throw std::out_of_range("can not pop empty vector");
  }
  int val = _data[--_size];
  if (_size <= _capacity / 4) {
    _resize(_capacity / 2);
  }

  return val;
}

int array_vector::find(int value) const { 
  for (int i = 0; i < _size; ++i) {
    if (value == at(i)) {
      return i;
    }
  }

  return -1;
}

void array_vector::insert(int index, int value) {
  // Assumes that index < size. This could be avoided if we had a good way to "fill in the gaps"
  if (0 > index || index >= _size) {
    throw std::out_of_range("index was outside range");
  }

  if (_size >= _capacity) {
    _resize(_capacity * 2);
  }

  std::memmove(_data + index + 1, _data + index, (_size - index) * sizeof(int));
  _data[index] = value;
  _size++;
}

void array_vector::del(int index) {
  if (0 > index || index >= _size) {
    throw std::out_of_range("index was outside range");
  }

  _size--;
  std::memmove(_data + index, _data + index + 1, (_size - index) * sizeof(int));

  if (_size <= _capacity / 4) {
    _resize(_capacity / 2);
  }
}

void array_vector::remove(int value) {
  for (int i = _size - 1; i >= 0; --i) {
    if (_data[i] == value) {
      del(i);
    }
  }
}

void array_vector::prepend(int value) {
  insert(0, value);
}

array_vector::array_vector() : MIN_CAPACITY(2), _data(new int[16]), _size(0), _capacity(16) {
}

array_vector::~array_vector() {
  delete[] _data;
}

int main() {
  array_vector v;

  std::cout << "v.capacity() = " << v.capacity();
  std::cout << "\tv.is_empty() = " << v.is_empty();
  std::cout << "\tv.at(0) = " << v.at(0);
  std::cout << "\t" << v << std::endl;

  for (int i = 0; i < 20; ++i) {
    v.push(i);

    std::cout << "v.capacity() = " << v.capacity();
    std::cout << "\t" << v << std::endl;
  }

  std::cout << "\n";
  std::cout << "v.find(5) = " << v.find(5) << std::endl;
  std::cout << "v.find(10000) = " << v.find(10000) << std::endl;
  std::cout << "\n";

  v.insert(10, 999);
  std::cout << v <<std::endl;

  v.del(5);
  std::cout << v <<std::endl;

  for (int i = 0; i < 20; ++i) {
    std::cout << "pop: " << v.pop() 
      << "\tv.size() = " << v.size()
      << "\tv.capacity() = " << v.capacity() << std::endl;
  }

  try {
    v.pop();
  } catch (const std::out_of_range& oor) {
    std::cerr << "Got oor: " << oor.what() << std::endl;
  }

  v.push(5);
  v.push(1);
  v.push(5);
  v.push(5);
  v.push(2);
  v.prepend(0);

  std::cout << v << std::endl;

  v.remove(5);
  std::cout << v << std::endl;


  return 0;
}
