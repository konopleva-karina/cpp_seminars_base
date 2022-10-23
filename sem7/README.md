### MergeSort

#### MergeSort

```C++
template <typename T>
T Copy(const T begin, const T end, T result) {
  for (int i = 0; begin + i != end; ++i) {
    *result = begin[i];
    ++result;
  }
  return result;
}

template <typename T>
T Merge(T first_begin, T first_end, T second_begin, T second_end, T result) {
  while (first_begin != first_end && second_begin != second_end) {
    if (*first_begin <= *second_begin) {
      *result = *first_begin;
      ++result;
      ++first_begin;
    } else {
      *result = *second_begin;
      ++result;
      ++second_begin;
    }
  }

  result = Copy(first_begin, first_end, result);
  result = Copy(second_begin, second_end, result);

  return result;
}

template <typename T>
void MergeSortImpl(T begin, T end, T result) {
  T result_it = result;
  size_t size = end - begin;

  if (size <= 1) {
    return;
  }

  MergeSortImpl(begin, begin + size / 2, result_it);
  MergeSortImpl(begin + size / 2, end, result_it);

  Merge(begin, begin + size / 2, begin + size / 2, end, result);
  Copy(result, result + size, begin);
}

template <typename T>
void MergeSort(T begin, T end, T result) {
  size_t size = end - begin;
  if (size <= 1) {
    return;
  }
  MergeSortImpl(begin, end, result);
}
```

#### InplaceMergeSort

TBD