//
// Created by oem on 23. 2. 6.
//

#include "vicon/vicon.hpp"
#include "raisim_message.hpp"

int main () {
  auto node = std::make_shared<vicon>("localhost", 200);
  node->connect();

  for (int i = 0; i < 100000; i++) {
    node->get_frame();
  }

  node->disconnect();

  return 0;
}

