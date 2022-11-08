#ifndef UNIQUE_H
#define UNIQUE_H

template <typename T>
T Unique(T begin, T end) {
  if (begin == end) {
    return end;
  }

  T unique_end = begin;
  while (++begin != end) {
    if (*unique_end != *begin && ++unique_end != begin) {
      *unique_end = *begin;
    }
  }
  return ++unique_end;
}

#endif  // UNIQUE_H