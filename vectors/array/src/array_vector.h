#ifndef _ARRAY_VECTOR_H
#define _ARRAY_VECTOR_H

class array_vector { 
  private:
    const int MIN_CAPACITY;
    int *_data;
    int _size;
    int _capacity;

    void _resize(int new_capacity);

  public:
    array_vector();
    ~array_vector();

    int size() const;
    int capacity() const;
    bool is_empty() const;
    int at(int i) const;
    int find(int value) const;

    void push(int value);
    int pop();

    void insert(int index, int value);
    void prepend(int value);
    void del(int index);
    void remove(int value);
};

std::ostream &operator<<(std::ostream &out, array_vector const &vec) {
  out << '[';
  for (int i = 0; i < vec.size(); ++i) {
    out << vec.at(i);
    if (i < vec.size() - 1) {
      out << ", ";
    }
  }
  return out << ']';
}

#endif
