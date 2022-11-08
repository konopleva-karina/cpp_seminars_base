#ifndef REMOVE_H
#define REMOVE_H

template <typename T, typename U>
T Find(T begin, T end, U value) {
  while (begin != end) {
    if (*begin == value) {
      break;
    } else {
      ++begin;
    }
  }
  return begin;
}

template <typename T, typename U>
T Remove(T begin, T end, U value) {
  T first = Find(begin, end, value);
  if (first != end) {
    for (T it = first + 1; it != end; ++it) {
      if (*it != value) {
        *(first++) = *it;
      }
    }
  }
  return first;
}

#endif  // REMOVE_H