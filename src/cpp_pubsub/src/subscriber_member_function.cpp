// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file publisher_member_function.cpp
 * @author Shelvin Pauly (spauly@umd.edu)
 * @brief Custom subscriber node
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "rclcpp/logging.hpp"

using std::placeholders::_1;
/**
 * @brief Subscriber Class
 * 
 */
class MinimalSubscriber : public rclcpp::Node {
 public:
  /**
   * @brief Construct a new Minimal Subscriber object
   * 
   */
  MinimalSubscriber()
  : Node("subscriber") {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

 private:
  /**
  * @brief topic callback function to collect data from topic
  * 
  * @param msg 
  */
  void topic_callback(const std_msgs::msg::String::SharedPtr msg) const {
    RCLCPP_INFO_STREAM(this->get_logger(),
    "I hear you, buddy. Keep going ! "<< msg->data);
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
