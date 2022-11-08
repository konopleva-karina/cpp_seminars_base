#ifndef ISSORTEDUNTIL_H
#define ISSORTEDUNTIL_H

template <typename T>
T IsSortedUntil(T begin, T end) {
  for (T it = begin + 1; it < end; ++it) {
    if (*it < *(it - 1)) {
      return it;
    }
  }
  return end;
}

#endif  // ISSORTEDUNTIL_H