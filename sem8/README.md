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
int LeftChild(int i) {
  return 2 * i + 1;
}

int RightChild(int i) {
  return 2 * i + 2;
}

int Parent(int i) {
  return (i - 1) / 2;
}
```

*Пирамида (heap)* - почти полное бинарное дерево, удовлетворящее "основному свойству пирамиды", то есть
- `Heap[Parent(i)] >= Heap[i] $\forall i \in$ [0, heap_size]` - такая пирамида называется невозрастающей
- `Heap[Parent(i)] >= Heap[i] $\forall i \in$ [0, heap_size]` для неубывающей пирамиды

#### Поддержка свойства пирамиды

```C++
void SiftDown(int* heap, int size, int i) {
  int left = LeftChild(i);
  int right = RightChild(i);
  int largest = i;
  if (left < size && heap[left] > heap[largest]) {
    largest = left;
  }
  if (right < size && heap[right] > heap[largest]) {
    largest = right;
  }
  if (largest != i) {
    Swap(heap[i], heap[largest]);
    SiftDown(heap, size, largest);
  }
}
```

#### Построение пирамиды
```C++
void BuildHeap(int* arr, int size) {
  for (int i = size / 2; i >= 0; --i) {
    SiftDown(arr, size, i);
  }
}
```
#### HeapSort

```C++
void HeapSort(int* arr, int size) {
  BuildHeap(int* arr, int size);
  for (int i = size; i >= 1; --i) {
    Swap(arr[0], arr[i]);
    --size;
    SiftDown(arr, size, 0);
  }
}
```

HeapSort работает по времени за $O(n \log n)$, $O(1)$ дополнительной памяти памяти, нестабильна.
