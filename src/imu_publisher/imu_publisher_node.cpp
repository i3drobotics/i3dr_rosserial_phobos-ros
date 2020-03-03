//! Imu (re)publisher node for Arduino Micro Adafruit BNO055 rosserial node.
/*!
 *  This node republishes the compact (excluding covariances) adafruit_bno055/Imu message from the Arduino Micro
 *  Adafruit BNO055 rosserial node as standard sensor_msgs/Imu messages, taking into account the calibration status of
 *  the BNO055 sensor.
 * 
 *  \file
 * 
 *  \author Maarten De Munck <maarten@vijfendertig.be>
 */


#include "imu_publisher.hpp"
#include <boost/program_options.hpp>
#include <ros/ros.h>


int main (int argc, char ** argv) {
  // Define namespace aliases.
  //namespace program_options = boost::program_options;

  // Get command line parameters.
  /*
  program_options::options_description description("Recognised options");
  description.add_options()
    ("help", "display this help and exit")
    ("frame-id", program_options::value<std::string>()->default_value("imu_link"),
      "frame_id to use on the published sensor_msgs/Imu messages (default: 'imu_link')");
  program_options::variables_map variables;
  program_options::store(program_options::parse_command_line(argc, argv, description), variables);
  program_options::notify(variables);
  */

  // Initialise Imu publisher node.
  ros::init(argc, argv, "adafruit_bno055_imu_publisher_node");
  ros::NodeHandle nh;
  ros::NodeHandle p_nh("~");
  std::string ns = ros::this_node::getNamespace();

  std::string frame_id, custom_ns;
  std::string frame_id_ = "bno055";
  std::string custom_ns_ = ns;

  //Get parameters
  if (p_nh.getParam("frame_id", frame_id))
  {
    frame_id_ = frame_id;
  }
  ROS_INFO("frame_id: %s", frame_id_.c_str());
  if (p_nh.getParam("namespace", custom_ns))
  {
    custom_ns_ = custom_ns;
  }
  ROS_INFO("namespace: %s", custom_ns_.c_str());

  // And GO!
  {
    rosserial_adafruit_bno055::ImuPublisher imu_publisher{frame_id_,custom_ns_};
    ros::spin();
  }

  // Take everything down.
  return EXIT_SUCCESS;
}