### Пирамида, пирамидальная сортировка

Вспомним определение бинарного дерева.

*Бинарное дерево* представляет собой конечное множество узлов, которое
- либо не содержит узлов
- либо состоит из трех непересекающихся множеств
    - корневого узла
    - бинарного дерева, называющегося левым поддеревом
    - бинарного дерева, называющегося правым поддеревом

Для каждого узла $i$ можно подсчитать его левого, правого ребёнка и родителя (если они существуют). Здесь индексация начинается с $0$.

```C++
int64_t LeftChild(int64_t i) {
  return 2 * i + 1;
}

int64_t RightChild(int64_t i) {
  return 2 * i + 2;
}

int64_t Parent(int64_t i) {
  return (i - 1) / 2;
}
```

*Пирамида (heap)* - почти полное бинарное дерево, удовлетворящее "основному свойству пирамиды", то есть
- $Heap[Parent(i)] >= Heap[i]\ \forall i \in [0, heapSize]$ - такая пирамида называется невозрастающей
- $Heap[Parent(i)] <= Heap[i]\ \forall i \in [0, heapSize]$ - такая пирамида называется неубывающей

#### Поддержка свойства пирамиды

```C++
template <typename T>
void SiftDown(T begin, T end, int64_t i) {
  int64_t size = end - begin;
  int64_t left = LeftChild(i);
  int64_t right = RightChild(i);
  int64_t largest = i;
  if (left < size && *(begin + largest) < *(begin + left)) {
    largest = left;
  }
  if (right < size && *(begin + largest) < *(begin + right)) {
    largest = right;
  }
  if (largest != i) {
    Swap(*(begin + i), *(begin + largest));
    SiftDown(begin, end, largest);
  }
}
```

#### Построение пирамиды
```C++
template <typename T>
void BuildHeap(T begin, T end) {
  int64_t size = end - begin;
  for (int64_t i = size / 2; i >= 0; --i) {
    SiftDown(begin, end, i);
  }
}
```
#### HeapSort

```C++
template <typename T>
void HeapSort(T begin,  T end) {
  BuildHeap(begin, end);
  int64_t size = end - begin;
  for (int64_t i = size - 1; i >= 1; --i) {
    Swap(*begin, *(begin + i));
    SiftDown(begin, --end, 0);
  }
}
```

HeapSort работает по времени за $O(n \log n)$, $O(1)$ дополнительной памяти памяти, нестабильна.
