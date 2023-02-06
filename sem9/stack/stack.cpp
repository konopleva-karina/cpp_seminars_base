#include <iostream>

class Stack {
  struct Node {
    int key;
    Node* next;

    explicit Node(int key): key(key), next(nullptr) {
    }
  };

  Node* head_;
  size_t size_;

public:
  Stack() : head_(nullptr), size_(0) {
  }

  void Push(int key) {
    auto new_node = new Node{key};
    new_node->next = head_;
    head_ = new_node;
    ++size_;
  }

  int Pop() {
    Node* node_to_pop = head_;
    int popped_val = head_->key;
    head_ = head_->next;
    delete node_to_pop;
    --size_;
    return popped_val;
  }

  size_t Size() const {
    return size_;
  }

  bool IsEmpty() const {
    return size_ == 0;
  }

  void Clear() {
    while (!IsEmpty()) {
      Pop();
    }
  }

  int Back() {
    return head_->key;
  }
};

int main() {
  Stack s;
  s.Push(1);
  s.Push(2);
  s.Pop();
  s.Push(4);
  std::cout << s.Back();
  s.Clear();
  std::cout << s.Size();
}