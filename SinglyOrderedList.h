#ifndef SINGLYORDEREDLIST_H
#define SINGLYORDEREDLIST_H
#include <iostream>
#include <fstream>
class SinglyOrderedList
{
public:
  SinglyOrderedList():
    head_(nullptr)
  {}
  SinglyOrderedList(const SinglyOrderedList&);
  SinglyOrderedList& operator=(const SinglyOrderedList&) = delete;
  SinglyOrderedList(SinglyOrderedList&&) noexcept;
  SinglyOrderedList& operator=(SinglyOrderedList&&) noexcept;
  bool insert(const std::string&);
  friend std::ofstream& operator<<(std::ofstream&, SinglyOrderedList&);
  virtual ~SinglyOrderedList();
private:
  struct Node
  {
    std::string item_;
    Node* next_;
    explicit Node(std::string item, Node* next = nullptr):
      item_(std::move(item)),
      next_(next)
    {}
  };
  Node* head_;
  void swap(SinglyOrderedList&);
};
#endif
