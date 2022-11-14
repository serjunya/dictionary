#include "SinglyOrderedList.h"
void SinglyOrderedList::swap(SinglyOrderedList& other) {
  std::swap(head_, other.head_);
}
SinglyOrderedList::SinglyOrderedList(const SinglyOrderedList& src):
  head_(src.head_)
{}
SinglyOrderedList::SinglyOrderedList(SinglyOrderedList&& other) noexcept :
  head_(other.head_)
{
  other.head_ = nullptr;
}
SinglyOrderedList& SinglyOrderedList::operator=(SinglyOrderedList&& right) noexcept {
  if (this != &right) {
    swap(right);
  }
  return *this;
}
bool SinglyOrderedList::insert(const std::string& item) {
  if (!head_) {
    head_ = new Node(item);
    return true;
  }
  if (item < head_->item_) {
    Node* x = new Node(item);
    x->next_ = head_;
    head_ = x;
    return true;
  }
  Node* current = head_;
  while(current) {
    if (current->item_ == item) {
      return false;
    }
    if (item > current->item_ && (!current->next_ || item < (current->next_)->item_)) {
      Node* x = new Node(item);
      x->next_ = current->next_;
      current->next_ = x;
      return true;
    }
    current = current->next_;
  }
  return false;
}
std::ofstream& operator<<(std::ofstream& out, SinglyOrderedList& list) {
  SinglyOrderedList::Node* current = nullptr;
  SinglyOrderedList::Node* next = list.head_;
  bool first = true;
  while (next) {
    if (!first)
      out << ", ";
    current = next;
    next = next->next_;
    out << current->item_;
    first = false;
  }
  return out;
}
SinglyOrderedList::~SinglyOrderedList() {
  Node* current = nullptr;
  Node* next = head_;
  while (next) {
    current = next;
    next = next->next_;
    delete current;
  }
}
