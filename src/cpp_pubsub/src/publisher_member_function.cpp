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
 * @brief Custom publisher node
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "cpp_pubsub/srv/change_my_message.hpp"

#include "rclcpp/logging.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

/**
 * @brief Publisher class
 * 
 */
class MinimalPublisher : public rclcpp::Node {
 public:
  /**
   * @brief Construct a new Minimal Publisher object
   * 
   */
  MinimalPublisher()
  : Node("publisher"), count_(0) {
    this->get_logger().set_level(rclcpp::Logger::Level::Debug);

    RCLCPP_DEBUG_STREAM(this->get_logger(),
                    " Getting frequency ");

    // Setting for custom frequency
    auto new_freq_msg = rcl_interfaces::msg::ParameterDescriptor();
    new_freq_msg.description = " Custom frequency for publisher";

    this->declare_parameter("new_freq", 1.0, new_freq_msg);
    auto new_freq = this->get_parameter("new_freq")
                  .get_parameter_value().get<std::float_t>();

    // Making checks for the new frequency
    if (new_freq == 0) {
        RCLCPP_WARN_STREAM(this->get_logger(),
                  " Frequency is set to be zero!! ");
         RCLCPP_FATAL_STREAM(this->get_logger(), " Cannot Publish Data ");
        
      } else if (new_freq == 0) {
        RCLCPP_ERROR_STREAM(this->get_logger(),
                  "Publisher frequency cannot be negative!");
      }

    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    // Calculate final frequency
    auto time = std::chrono::milliseconds(
            static_cast<int>(1000/new_freq));

    timer_ = this->create_wall_timer(
      time, std::bind(&MinimalPublisher::timer_callback, this));

    auto serviceCallbackPtr = std::bind(&MinimalPublisher::change_message,
                    this, std::placeholders::_1, std::placeholders::_2);

    service_ = create_service<cpp_pubsub::srv::ChangeMyMessage>(
                    "change_message", serviceCallbackPtr);
  }

  /**
   * @brief Implementing the service change message
   * 
   * @param request 
   * @param response 
   */
  void change_message(
    const std::shared_ptr<cpp_pubsub::srv::ChangeMyMessage::Request> request,
    std::shared_ptr<cpp_pubsub::srv::ChangeMyMessage::Response> response) {
    response->out_string = request->in_string +
             " I apologize but we need to change the message!!!";
    RCLCPP_INFO_STREAM(this->get_logger(),
                  "Request message: "<< request->in_string);
    RCLCPP_INFO_STREAM(this->get_logger(),
                  "Response message: "<< response->out_string);
  }

 private:
  /**
   * @brief callback function
   * 
   */
  void timer_callback() {
    auto message = std_msgs::msg::String();
    message.data = "Hello, this is Shelvin speaking. Count: "
    + std::to_string(count_++);
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: " << message.data);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::Service<cpp_pubsub::srv::ChangeMyMessage>::SharedPtr service_;
  size_t count_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
