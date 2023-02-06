### Стек и очередь

Пищем реализацию стека на односвязном списке и очереди на двусвязном.

#### Стек

[Реализация](https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem9/stack/stack.cpp)

На самом деле на прошлых семинарах мы уже говорили про стек. Например, упоминали стек вызовов, когда разбирали рекурсию.

Посмотрите на картинку

![](https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem9/stack/stack.png)


Мы умеем класть элементы на вершину стека и доставать элемент, лежащий на вершине. То есть стек организован по принципу LIFO (last in, first out).
В этом плане стек похож на стопку тарелок. Будем хранить указатель на вершину стека и назовём его head.

Вот как происходит добавление в стек:

![](https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem9/stack/stack_push.png)
#### Очередь

[Реализация](https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem9/queue/queue.cpp)

С очередью каждый встречался в обычной жизни, например, с очередью на кассу в магазине. Новые элементы приходят в конец очереди,
достаём из очереди элементы, стоящие в начале. То есть очередь организована по принципу FIFO (first in, first out). 
Для очереди будем хранить указатель на начало - head и на конец - tail.

![](https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem9/queue/queue.png)

Добавление в очередь:

![](https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem9/queue/queue_push.png)
