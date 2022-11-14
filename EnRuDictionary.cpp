#include "EnRuDictionary.h"
EnRuDictionary::EnRuDictionary():
  root_(nullptr),
  size_(0)
{}
EnRuDictionary::EnRuDictionary(EnRuDictionary&& src) noexcept:
  root_(src.root_),
  size_(src.size_)
{
  src.root_ = nullptr;
  src.size_ = 0;
}
EnRuDictionary& EnRuDictionary::operator=(EnRuDictionary&& src) noexcept
{
  if (this != &src)
  {
    swap(src);
  }
  return *this;
}
EnRuDictionary::~EnRuDictionary() {
  destruct(root_);
}
bool EnRuDictionary::insert(const std::string &key, SinglyOrderedList value) {
  Node* y = nullptr;
  Node* x = root_;
  while (x) {
    if (x->key_ == key) {
      return false;
    }
    y = x;
    if (key < x->key_) {
      x = x->left_;
    }
    else {
      x = x->right_;
    }
  }
  Node* z = new Node(key, std::move(value),  nullptr, nullptr, y);
  ++size_;
  if (!y) {
    root_ = z;
    return true;
  }
  else if (key < y->key_) {
    y->left_ = z;
    return true;
  }
  else {
    y->right_ = z;
    return true;
  }
}
bool EnRuDictionary::setValue(const std::string& word, const std::string& translation)
{
  Node *x = iterativeSearchNode(word);
  if (x)
  {
    x->value_.insert(translation);
    return true;
  }
  return false;
}
bool EnRuDictionary::printWord(std::ofstream& out, const std::string &word)
{
  Node *x = iterativeSearchNode(word);
  if (x)
  {
    out << x->key_ << " - ";
    out << x->value_;
    out << '\n';
    return true;
  }
  return false;
}
bool EnRuDictionary::deleteKey(const std::string& key) {
  Node* current = root_;
  while (current && current->key_ != key) {
    if (key > current->key_) {
      current = current->right_;
    }
    else current = current->left_;
  }
  if (!current)
    return false;
  if (!current->left_ && !current->right_) {
    if (!current->p_) {
      delete current;
      root_ = nullptr;
      return true;
    }
    if (current->p_->right_ && current->p_->right_->key_ == current->key_) {
      current->p_->right_ = nullptr;
      delete current;
      --size_;
      return true;
    }
    else if (current->p_->left_ && current->p_->left_->key_ == current->key_) {
      current->p_->left_ = nullptr;
      delete current;
      --size_;
      return true;
    }
  }
  else if (current->right_ && !current->left_ && !current->p_) {
    Node *useless = current;
    current = current->right_;
    current->p_ = nullptr;
    root_ = root_->right_;
    delete useless;
    --size_;
    return true;
  }
  else if (!current->right_ && current->left_ && !current->p_) {
    Node* useless = current;
    current = current->left_;
    current->p_ = nullptr;
    root_ = root_->left_;
    delete useless;
    --size_;
    return true;
  }
  else if (!current->right_ && current->left_ && current->p_) {
    if (current->p_->right_->key_ == key) {
      Node* useless = current;
      current->p_->right_ = current->left_;
      delete useless;
      --size_;
      return true;
    }
    else if (current->p_->left_->key_ == key) {
      Node* useless = current;
      current->p_->left_ = current->left_;
      delete useless;
      --size_;
      return true;
    }
  }
  else if (current->right_ && !current->left_ && current->p_) {
    if (current->p_->right_->key_ == key) {
      Node* useless = current;
      current->p_->right_ = current->right_;
      delete useless;
      --size_;
      return true;
    }
    else if (current->p_->left_->key_ == key) {
      Node* useless = current;
      current->p_->left_ = current->right_;
      delete useless;
      --size_;
      return true;
    }
  }
  if (current->right_ && current->left_ && current->p_) {
    Node* useless = current;
    Node *temp = next(current);
    std::swap(useless->key_, temp->key_);
    std::swap(useless->value_, temp->value_);
    if (temp->p_->left_->key_ == temp->key_)
      temp->p_->left_ = nullptr;
    else if (temp->p_->right_->key_ == temp->key_)
      temp->p_->right_ = nullptr;
    delete temp;
    --size_;
    return true;
  }
  else if (current->right_ && current->left_ && !current->p_) {
    Node* useless = current;
    Node* temp = next(current);
    current = current->right_;
    temp->left_ = useless->left_;
    useless->left_->p_ = temp;
    current->p_ = nullptr;
    root_ = root_->right_;
    delete useless;
    --size_;
    return true;
  }
  return false;
}
bool EnRuDictionary::empty() const {
  return !size_;
}
void EnRuDictionary::print(std::ofstream& out) const {
  printNode(out, root_);
}
EnRuDictionary::Node* EnRuDictionary::next(Node* node) {
  if (node->right_) {
    return minimum(node->right_);
  }
  Node* y = node->p_;
  while (y && node == y->right_) {
    node = y;
    y = y->p_;
  }
  return y;
}
void EnRuDictionary::swap(EnRuDictionary &other) {
  std::swap(root_, other.root_);
}
void EnRuDictionary::destruct(Node* node) {
  if (node) {
    destruct(node->left_);
    destruct(node->right_);
    delete node;
  }
}
EnRuDictionary::Node* EnRuDictionary::minimum(Node* node) {
  while (node->left_) {
    node = node->left_;
  }
  return node;
}
EnRuDictionary::Node *EnRuDictionary::iterativeSearchNode(const std::string& key) const {
  Node *x = root_;
  while(x && x->key_ != key) {
    if (key < x->key_) {
      x = x->left_;
    }
    else {
      x = x->right_;
    }
  }
  return x;
}
void EnRuDictionary::printNode(std::ofstream& out, Node* root) const {
  if (root)
  {
    if (root->left_) printNode(out, root->left_);
    out << root->key_ << " - ";
    out << root->value_;
    out << '\n';
    if (root->right_) printNode(out, root->right_);
  }
}
