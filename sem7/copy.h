#ifndef COPY_H
#define COPY_H

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
  while (src_begin != src_end) {
    *(dest++) = *(src_begin++);
  }
  return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest_end) {
  while (src_end != src_begin) {
    *(--dest_end) = *(--src_end);
  }
  return dest_end;
}

#endif  // COPY_H