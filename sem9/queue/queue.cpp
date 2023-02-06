#include <iostream>

class Queue {
  struct Node {
    int key;
    Node* next;
    Node* prev;

    explicit Node(int val, Node* next=nullptr, Node* prev=nullptr) : key(val), next(next), prev(prev) {
    }
  };

  Node* head_;
  Node* tail_;
  size_t size_;

public:
  Queue() : head_(nullptr), tail_(nullptr), size_(0) {
  }

  size_t Size() const {
    return size_;
  }

  bool IsEmpty() const {
    return size_ == 0;
  }

  void Push(int val) {
    auto new_node = new Node{val};
    new_node->next = tail_;

    if (!IsEmpty()) {
      tail_->prev = new_node;
    }

    tail_ = new_node;
    if (IsEmpty()) {
      head_ = new_node;
    }
    ++size_;
  }

  int Pop() {
    Node* popped_node = head_;
    int popped_val = head_->key;
    head_ = head_->prev;
    if (size_ > 1) {
      head_->next = nullptr;
    }
    --size_;
    if (IsEmpty()) {
      tail_ = nullptr;
    }
    delete popped_node;
    return popped_val;
  }

  int Front() {
    return head_->key;
  }

  int Back() {
    return tail_->key;
  }

  void Clear() {
    while (!IsEmpty()) {
      Pop();
    }
  }
};

int main() {
  Queue q;

  q.Push(1);
  q.Push(2);
  q.Push(3);
  q.Pop();
  q.Pop();
  q.Pop();
  q.Push(4);
  q.Push(5);
  std::cout << q.Back() << ' ' << q.Front();
  q.Clear();
}