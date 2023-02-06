//
// Created by oem on 23. 2. 6.
//

#include "vicon.hpp"

vicon::vicon(std::string host_address, const int buffer_size) {
  this->host_address = host_address;
  this->buffer_size = buffer_size;
}
//
vicon::~vicon() {
//  delete this->client_;
//  delete this->cfg_;
}

bool vicon::connect() {

  while (!client_.IsConnected().Connected) {
    bool success = client_.Connect(host_address);
    if(success)
      break;
    RSINFO("Connecting")
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }


  client_.EnableSegmentData();
  client_.EnableMarkerData();
  RSFATAL_IF(client_.EnableMarkerData().Result != Result::Success, "Enable Marker Data Failed")
  RSFATAL_IF(client_.EnableSegmentData().Result != Result::Success, "Enable Segment Data Failed")
  client_.SetStreamMode(StreamMode::ClientPull);
  client_.SetBufferSize(buffer_size);
  return true;
}

bool vicon::disconnect() {
  if (!client_.IsConnected().Connected)
    return true;
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  client_.DisableMarkerData();
  client_.Disconnect();
  RSFATAL_IF(client_.IsConnected().Connected, "Disconnect Failed")
  return true;
}

void vicon::get_frame() {
  std::clock_t start, finish;
  double duration;

  start = clock();

  client_.GetFrame();
  Output_GetFrameNumber frame_number = client_.GetFrameNumber();
  RSINFO("Frame number : " << frame_number.FrameNumber)
  unsigned int subject_num = client_.GetSubjectCount().SubjectCount;
  RSINFO("subject num : " << subject_num)
  for (unsigned int subject_idx = 0; subject_idx < subject_num; subject_idx ++) {
    string subject_name = client_.GetSubjectName(subject_idx).SubjectName;
    RSINFO("subject name : " << subject_name)
    unsigned  int segment_num = client_.GetSegmentCount(subject_name).SegmentCount;
    for (unsigned  int segment_idx = 0; segment_idx < segment_num; segment_idx ++) {
      string segment_name = client_.GetSegmentName(subject_name, segment_idx).SegmentName;
      RSINFO("segment_name : " << segment_name)
      PoseStruct pose;
      Output_GetSegmentGlobalTranslation trans =
          client_.GetSegmentGlobalTranslation(subject_name, segment_name);
      Output_GetSegmentGlobalRotationMatrix rot =
          client_.GetSegmentGlobalRotationMatrix(subject_name, segment_name);

      for(size_t i = 0; i<3; i++)
        pose.translation(i) = trans.Translation[i];
      for(size_t i = 0; i<9; i++)
        pose.rotation(i) = rot.Rotation[i];

      pose.subject_name = subject_name;
      pose.segment_name = segment_name;
      pose.frame_number = frame_number.FrameNumber;
      pose.translation_type = "Global";

      RSINFO("translation : " << pose.translation)
      RSINFO("rotation : " << pose.rotation)

    }
  }

  finish = clock();

  duration = (double)(finish - start) / CLOCKS_PER_SEC;

  RSINFO("time using : " << duration)
  RSINFO("----------------------------")
}



