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

Пока что не в терминах begin-end и без шаблонов (TBD)

```C++
template <typename T>
void Swap(T& lhs, T& rhs) {
  int tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

template <typename T, typename U>
T LowerBound(T begin, T end, U value) {
  int64_t size = end - begin;
  T it;
  while (size > 0) {
    it = begin;
    int64_t step = size / 2;
    it += step;
    if (*it < value) {
      begin = ++it;
      size -= step + 1;
    } else {
      size = step;
    }
  }
  return begin;
}

template <typename T, typename U>
T UpperBound(T begin, T end, U value) {
  int64_t size = end - begin;
  T it;
  while (size > 0) {
    it = begin;
    int64_t step = size / 2;
    it += step;
    if (*it <= value) {
      begin = ++it;
      size -= step + 1;
    } else {
      size = step;
    }
  }
  return begin;
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

template <typename T>
void InplaceMerge(T first_beg, T first_end, T second_beg, T second_end) {
  size_t first_part_size = first_end - first_beg;
  size_t second_part_size = second_end - second_beg;

  if (first_part_size == 0 || second_part_size == 0) {
    return;
  }

  if (first_part_size == 1 && second_part_size == 1) {
    if (*second_beg < *first_beg) {
      Swap(*first_beg, *second_beg);
    }
    return;
  }

  T B1_beg = first_beg;
  T B1_end;

  T B2_beg;
  T B3_beg = second_beg;

  T B3_end;

  T B4_beg;
  T B4_end = second_end;

  if (first_part_size >= second_part_size) {
    B1_end = B1_beg + first_part_size / 2;
    B2_beg = B1_end;
    T sep = LowerBound(second_beg, second_end, *B2_beg);
    B3_end = sep;
    B4_beg = sep;
  } else {
    B3_end = B3_beg + second_part_size / 2;
    B4_beg = B3_end;
    T sep = UpperBound(first_beg, first_end, *B4_beg);
    B1_end = sep;
    B2_beg = sep;
  }

  Rotate(B2_beg, B3_beg, B3_end);
  size_t B3_size = B3_end - B3_beg;
  InplaceMerge(B1_beg, B1_end, B2_beg, B2_beg + B3_size);
  InplaceMerge(B2_beg + B3_size, B3_end, B4_beg, B4_end);
}


template <typename T>
void MergeSort(T begin, T end) {
  size_t size = end - begin;

  if (size <= 1) {
    return;
  }

  MergeSort(begin, begin + size / 2);
  MergeSort(begin + size / 2, end);

  InplaceMerge(begin, begin + size / 2, begin + size / 2, end);
}
```

#### Почему нельзя писать реализацию шаблонных функций в .cpp файлах

Допустим, мы хотим написать модуль, содержащий функцию Swap. У нас есть три файла: main.cpp, swap.h, swap.cpp. Их содержимое приведено ниже.
```C++
// swap.h
#ifndef SWAP_H
#define SWAP_H

template<typename T>
void Swap(T& lhs, T& rhs);

#endif

//swap.cpp
#include "swap.h"

template<typename T>
void Swap(T& lhs, T& rhs) {
  T tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

//main.cpp
#include "swap.h"

int main() {
  int x = 3;
  int y = 4;
  Swap(x, y);
}
```

Данная программа скомпилируется, но упадёт на этапе линковки со следующей ошибкой
```bash
Undefined symbols for architecture x86_64:
  "void Swap<int>(int&, int&)", referenced from:
      _main in main-2ee172.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

Поймём, в чём проблема. В `main.cpp` присутсвует директива `#include`, которая на этапе препроцессинга подставляет в файл объявление функции `Swap`. Когда мы вызываем `Swap` в шестой строчке main'а, компилятор понимает, что подставить вместо `T` в объявление функции `Swap`. Затем отдельно происходит компиляция модуля, состоящего из `swap.cpp` и `swap.h`. Но здесь непонятно, как инстанцировать шаблон, кодогенерации не происходит, из-за чего у функции `Swap` нет определения и код падает с ошибкой линковки.

Решение: **помещать и объявление, и определение шаблонных функций в заголовочный файл**. 
