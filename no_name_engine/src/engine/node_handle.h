#pragma once

namespace nn {

class Node;

// Lightweight handle to refer to a Node within a Scene
class NodeHandle {
public:
  NodeHandle() : ptr_(nullptr) {}
  explicit NodeHandle(Node *node) : ptr_(node) {}

  bool IsValid() const { return ptr_ != nullptr; }
  Node *Get() const { return ptr_; }

  bool operator==(const NodeHandle &other) const { return ptr_ == other.ptr_; }
  bool operator!=(const NodeHandle &other) const { return !(*this == other); }

private:
  Node *ptr_;
};

} // namespace nn