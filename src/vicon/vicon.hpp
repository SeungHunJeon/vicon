//
// Created by oem on 23. 2. 6.
//

#ifndef VICON_SRC_VICON_HPP_
#define VICON_SRC_VICON_HPP_

#include "DataStreamClient.h"
#include "iostream"
#include <string>
#include "raisim_message.hpp"
#include "thread"
#include "eigen3/Eigen/Core"

//#include <rclcpp/rclcpp.hpp>

using namespace std;
using namespace ViconDataStreamSDK::CPP;

struct PoseStruct
{
  Eigen::Vector3d translation;
  Eigen::Matrix3d rotation;
  std::string subject_name;
  std::string segment_name;
  std::string translation_type;
  unsigned int frame_number;
} typedef PoseStruct;


class vicon {
 public:
  vicon(std::string hostname, const int buffer_size);

  ~vicon();

  bool connect();

  bool disconnect();

  void get_frame();

 private:
  ViconDataStreamSDK::CPP::Client client_;
  string hostname;
  unsigned int buffer_size;
};

#endif //VICON_SRC_MAIN_HPP_
