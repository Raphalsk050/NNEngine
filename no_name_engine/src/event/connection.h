#pragma once

#include <cstdint>

namespace nn {

using ConnectionId = uint64_t;

// Represents a subscription handle. Use to disconnect.
class Connection {
public:
  Connection() : id_(0) {}
  explicit Connection(ConnectionId id) : id_(id) {}
  ConnectionId GetId() const { return id_; }
  bool IsValid() const { return id_ != 0; }

private:
  ConnectionId id_;
};

} // namespace nn
