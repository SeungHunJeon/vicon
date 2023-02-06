//
// Created by oem on 23. 2. 6.
//

#include "vicon/vicon.hpp"
#include "raisim_message.hpp"

int main () {
  auto node = std::make_shared<vicon>("192.168.0.3", 200);
  RSINFO(1)
  node->connect();
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    RSINFO(1)
  for (int i = 0; i < 10000000000; i++) {
    node->get_frame();
  }

  node->disconnect();

  return 0;
}

