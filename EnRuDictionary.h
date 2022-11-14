#ifndef ENRUDICTIONARY_H
#define ENRUDICTIONARY_H
#include "SinglyOrderedList.h"
class EnRuDictionary
{
public:
  EnRuDictionary();
  EnRuDictionary(const EnRuDictionary&) = delete;
  EnRuDictionary(EnRuDictionary&&) noexcept;
  EnRuDictionary& operator=(const EnRuDictionary&) = delete;
  EnRuDictionary& operator=(EnRuDictionary&&) noexcept;
  virtual ~EnRuDictionary();
  bool insert(const std::string&, SinglyOrderedList);
  bool setValue(const std::string&, const std::string&);
  bool printWord(std::ofstream&, const std::string&);
  bool deleteKey(const std::string&);
  bool empty() const;
  void print(std::ofstream&) const;
private:
  struct Node
  {
    std::string key_;
    SinglyOrderedList value_;
    Node *left_;
    Node *right_;
    Node *p_;
    explicit Node(
    std::string key, SinglyOrderedList value,
    Node *left = nullptr, Node *right= nullptr, Node *p =nullptr):
      key_(std::move(key)),
      value_(std::move(value)),
      left_(left),
      right_(right),
      p_(p)
    {}
  };
  Node *root_;
  std::size_t size_;
  Node* next(Node*);
  void swap(EnRuDictionary&);
  void destruct(Node*);
  Node* minimum(Node*);
  Node *iterativeSearchNode(const std::string&) const;
  void printNode(std::ofstream&, Node*) const;
};
#endif
