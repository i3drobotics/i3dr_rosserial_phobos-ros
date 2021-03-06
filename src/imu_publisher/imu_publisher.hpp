//! Imu (re)publisher for Arduino Micro Adafruit BNO055 rosserial node.
/*!
 *  This node republishes the compact (excluding covariances) adafruit_bno055/Imu message from the Arduino Micro
 *  Adafruit BNO055 rosserial node as standard sensor_msgs/Imu messages, taking into account the calibration status of
 *  the BNO055 sensor.
 * 
 *  \file
 * 
 *  \author Maarten De Munck <maarten@vijfendertig.be>
 */


#ifndef __ROS_ADAFRUIT_BNO055__IMU_PUBLISHER__
#define __ROS_ADAFRUIT_BNO055__IMU_PUBLISHER__


#include <ros/ros.h>
#include <i3dr_rosserial_phobos/Imu.h>
#include <i3dr_rosserial_phobos/CalibrationStatus.h>
#include <visualization_msgs/Marker.h>
#include "tf2_ros/transform_broadcaster.h"
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>

namespace i3dr_rosserial_phobos {

  class ImuPublisher {
    private:
      ros::NodeHandle node_handle_;
      ros::Subscriber subscriber_compact_imu_;
      ros::Subscriber subscriber_calibration_status_;
      ros::Publisher publisher_full_imu_;
      ros::Publisher publisher_imu_mag_;
      std::string frame_id_;
      std::string ns_;
      bool publish_tf_;
      i3dr_rosserial_phobos::CalibrationStatus cached_calibration_status_;
    public:
      ImuPublisher(const std::string & frame_id, const std::string & ns, bool publish_tf_);
      ~ImuPublisher() = default;
      void compactImuCallback(const Imu::ConstPtr & message);
      void calibrationStatusCallback(const CalibrationStatus::ConstPtr & message);
      void publishTransform(const Imu::ConstPtr & message);
  };

}


#endif