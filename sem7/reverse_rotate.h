#ifndef ROTATE_H
#define ROTATE_H

template <typename T>
void Swap(T& lhs, T& rhs) {
  T tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

template <typename T>
void Reverse(T begin, T end) {
  if (begin + 1 == end) {
    return;
  }

  while (begin < end) {
    Swap(*(begin++), *(--end));
  }
}

template <typename T>
void Rotate(T begin, T mid, T end) {
  Reverse(begin, mid);
  Reverse(mid, end);
  Reverse(begin, end);
}

#endif  // ROTATE_H