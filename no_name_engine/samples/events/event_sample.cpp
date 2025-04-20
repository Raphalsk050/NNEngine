#include <chrono>
#include <no_name_engine.h>
#include <thread>

namespace nn {

/*
 * This example will create two events and will dispatch them after an amount
 * of time to the related nodes
 */
int main() {
  auto dispatcher = Dispatcher();
  auto node = new Node();
  auto node_2 = new Node();
  auto some_event = Event();

  dispatcher.Connect(node, 0, [](Event &e) {
    DebugHelper::NLog_info("Event received");
    e.StopPropagation();
  });

  dispatcher.Connect(node_2, 0, [](Event &e) {
    DebugHelper::NLog_info("Event_2 received");
    e.StopPropagation();
  });

  std::this_thread::sleep_for(std::chrono::seconds(2));
  dispatcher.Dispatch(node, 0, some_event);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  dispatcher.Dispatch(node_2, 0, some_event);

  return 0;
}
} // namespace nn
