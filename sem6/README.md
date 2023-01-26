### Быстрая сортировка, строки

Напишем рекурсивную реализацию быстрой сортировки. Функция `QuickSort` принимает на вход массив `arr`, сортирует его по возрастанию и ничего не возвращает. Функция `QuickSortImpl` сортирует подмассив `arr[low:high]` исходного массива. Чтобы отсортировать исходных массив, необходимо отсортировать подмассив `arr[0:arr_size]`.

Если `low >= high`, то либо подмассив пустой и нам нечего сортировать, либо он состоит из одного элемента, который можно считать отсортированным массивом. Иначе вызываем функцию `Partition`, которая выбирает некоторый индекс `pivot_idx` - назовём элемент по этому индексу опорным - и модифицирует подмассив `arr[low:high]` так, что все элементы подмассива `arr[low:pivot_idx]` не больше элементов подмассива `arr[pivot_idx:high]`. Далее рекурсивно запускаем функцию `QuickSortImpl` на двух полученных подмассивах.

```C++
void  QuickSortImpl(int* arr, int low, int high) {
  if (low >= high) {
    return;
  }
  int pivot_idx = Partition(arr, low, high);
  QuickSortImpl(arr, low, pivot_idx);
  QuickSortImpl(arr, pivot_idx + 1, high);
}

void  QuickSort(int* arr, int size) {
  QuickSortImpl(arr, 0, size - 1);
}
```

Как вы уже догадались, функцию `Partition` (разбиение) можно реализовать несколькими способами. Мы разберём
- разбиение Ломуто
- разбиение Хоара
- разбиение на три части

#### Быстрая сортировка с разбиением Ломуто

В данной реализации в качестве опорного берём последний элемент подмассива `arr[high]`.

```C++
void Swap(int& lhs, int& rhs) {
  int tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

int Partition(int* arr, int low, int high) {
  int pivot = arr[high];
  int i = low;
  for (int j = low; j < high; ++j) {
    if (arr[j] <= pivot) {
      Swap(arr[i], arr[j]);
      ++i;
    }
  }
  Swap(arr[i], arr[high]);
  return i;
}

void QuickSortImpl(int* arr, int low, int high) {
  if (low >= high) {
    return;
  }
  int pivot_idx = Partition(arr, low, high);
  QuickSortImpl(arr, low, pivot_idx - 1);
  QuickSortImpl(arr, pivot_idx + 1, high);
}

void QuickSort(int* arr, int size) {
  QuickSortImpl(arr, 0, size - 1);
}
```

#### Быстрая сортировка с разбиением Хоара

```C++
void Swap(int& lhs, int& rhs) {
  int tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}


int Partition(int* arr, int low, int high) {
  int pivot = arr[(low + high) / 2];
  int i = low;
  int j = high;
  while (true) {
    while (arr[i] < pivot) {
      i += 1;
    }
    while (arr[j] > pivot) {
      j -= 1;
    }
    if (i >= j) {
      return j;
    }
    Swap(arr[i++], arr[j--]);
  }
}

void  QuickSortImpl(int* arr, int low, int high) {
  if (low >= high) {
    return;
  }
  int pivot_idx = Partition(arr, low, high);
  QuickSortImpl(arr, low, pivot_idx);
  QuickSortImpl(arr, pivot_idx + 1, high);
}

void  QuickSort(int* arr, int size) {
  QuickSortImpl(arr, 0, size - 1);
}
```

Опорный элемент можно выбирать по-разному. Рассмотрим несколько способов.
1. Первый или последний элементы - плохой выбор, если массив уже отсортирован.
2. Средний элемент (как в этой реализации).
3. Элемент по случайному индексу. `std::rand()/((RAND_MAX + 1u)/arr_size)` выдаст псевдослучайный индекс в массиве размера `arr_size`.
4. Медиана первого, среднего и последнего элементов (смотрите реализацию ниже).

#### Быстрая сортировка с разбиением на три части

Разбиение на 3 части используется в случае, когда в массиве много повторяющихся элементов.

```C++
void Swap(int& lhs, int& rhs) {
  int tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

int FindMedian(int* arr, int low, int high) {
  int mid_idx = low + (high - low) / 2;

  if (arr[mid_idx] < arr[low]) {
    Swap(arr[low], arr[mid_idx]);
  }

  if (arr[high] < arr[low]) {
    Swap(arr[low], arr[high]);
  }

  if (arr[high] < arr[mid_idx]) {
    Swap(arr[high], arr[mid_idx]);
  }

  return mid_idx;
}

void ThreeWayPartition(int* arr, int low, int high, int& less_board, int& more_board) {
  less_board = low;
  more_board = high;

  // Index of the median of arr[low], arr[high], arr[low + (high - low) / 2]
  int mid_idx = FindMedian(arr, low, high);

  int pivot = arr[mid_idx];

  int idx = low;
  while (idx <= more_board) {
    if (arr[idx] < pivot) {
      Swap(arr[less_board], arr[idx]);
      ++idx;
      ++less_board;
    } else if (arr[idx] > pivot) {
      Swap(arr[more_board], arr[idx]);
      --more_board;
    } else {
      ++idx;
    }
  }
}

void QuickSortImpl(int* arr, int low, int high) {
  if (low >= high) {
    return;
  }

  // Everything to the left of less_board is smaller than the pivot
  int less_board = low;

  // Everything to the right of more_board is greater than the pivot
  int more_board = high;

  // Calculates less_board and right_board
  ThreeWayPartition(arr, low, high, less_board, more_board);

  QuickSortImpl(arr, low, less_board - 1);
  QuickSortImpl(arr, more_board + 1, high);
}

void QuickSort(int* arr, int size) {
  QuickSortImpl(arr, 0, size - 1);
}
```

#### Строки
C-style строка - это последовательность char'ов, завершающаяся терминальным символом `'\0'` (символ с кодом 0 в таблице ASCII). Строки во многом похожи на массивы. Далее для краткости будем называть c-style строки просто строками.

Ниже даны варианты создания строк. Терминальный символ в конец строки добавляется автоматически.
```C++
char str[]{"abc"};
char str2[] = "abс";
```

Так как строки являются массивами,
1. для строк определена операция взятия элемента по индексу

```C++
for (int i = 0; i < 3; ++i) {
    std::cout << str[i] << ' ';
} // a b c
```

2. нельзя присваивать одну строку другой

```C++
  str2 = str; // CE
```

##### [Функции для работы со строками](https://cplusplus.com/reference/cstring/) 
Определены в заголовочном файле `cstring`. Основные из них:
1. `strlen` вычисляет длину строки без учета терминального символа

```C++
  char str[]{"abc"};
  std::cout << strlen(str) << '\n'; // 3
  std::cout << sizeof(str) << '\n'; // 4
```

Замечание: strlen работает за линию от длины строки, поэтому не используйте её в условии выхода из циклов. 
Пример ниже отработает за квадрат от длины строки!

```C++
  char str[]{"Hello world!"};
  for (size_t i = 0; i < strlen(str); ++i) {
    std::cout << str[i];
  }
```

Работает за линию:

```C++
  char str[]{"Hello world!"};
  size_t len = strlen(str);
  for (size_t i = 0; i < len; ++i) {
    std::cout << str[i];
  }
```

2. `strcmp` сравнивает две строки str1 и str2 в лексикографическом порядке и возвращает
* 0, если строки равны
* значение < 0, если str1 < str2
* значение > 0, если str1 > str2

```C++
  char str1[]{"abc"};
  char str2[]{"adc"};
  std::cout << strcmp(str1, str1); // 0
  std::cout << strcmp(str1, str2); // -2
  std::cout << strcmp(str2, str1); // 2
```

3. `strcpy(char* dest, const char* src)` копирует строку src в dest

```C++
char str[256];
strcpy(str, "I'll dance dance dance with my hands");
std::cout << str; // I'll dance dance dance with my hands
```

4. `strcat(char* dest, const char* src)` добавляет копию строки src в конец строки dest

```C++
  char str[]{"Hello"};
  strcat(str," world!");
  std::cout << str; // Hello world!
```

5. `strstr(const char* str1, const char* str2)` находит первое вхождение строки str2 в строке str2 и 
возвращает указатель на него, иначе возвращает nullptr

```C++
  char str[]{"Hello world!"};

  char* world_ptr = strstr(str, "world");
  std::cout << world_ptr - str; // 6

  char* kek_ptr = strstr(str, "kek");
  std::cout << (kek_ptr == nullptr); // 1
```

##### size_t

Это беззнаковый целочисленный тип. Он же возвращается из функции sizeof(), size_t можно использовать для итерации по массиву:

```C++
  size_t len = 10;
  int* arr = new int[len];
  for (size_t i = 0; i < len; ++i) {
    std::cin >> arr[i];
  }
  delete[] arr;
```

size_t определен и в других библиотеках, например, в cstddef (странно подключатть cstring, если нужен только size_t). 
Подробнее про size_t на [cppreference](https://en.cppreference.com/w/cpp/types/size_t).