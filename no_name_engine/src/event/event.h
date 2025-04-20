#pragma once

#include <cstdint>

namespace nn {

// Define how events propagate through the node hierarchy
enum class PropagationMode : uint8_t {
  BubbleUp,    // from target up to root
  CaptureDown, // from root down to target
  Direct       // only to target
};

// Base class for all events. Users derive their own events from this.
class Event {
public:
  Event() : mode_(PropagationMode::BubbleUp), handled_(false) {}
  virtual ~Event() = default;

  // Get/Set propagation mode
  PropagationMode GetMode() const { return mode_; }
  void SetMode(PropagationMode m) { mode_ = m; }

  // Mark event as handled to stop further propagation
  bool IsHandled() const { return handled_; }
  void StopPropagation() { handled_ = true; }

private:
  PropagationMode mode_;
  bool handled_;
};

} // namespace nn