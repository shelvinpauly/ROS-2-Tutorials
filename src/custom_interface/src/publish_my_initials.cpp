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

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
// Include the header of our newly created MyName.msg
#include "custom_interface/msg/my_name.hpp"

using namespace std::chrono_literals;

class MyInitialsPublisher : public rclcpp::Node
{
public:
// Create a node and an Initials publisher.
  MyInitialsPublisher()
  : Node("my_initials_publisher")
  {
    my_initials_publisher_ =
      this->create_publisher<custom_interface::msg::MyName>("my_initials", 10);

    // Create a callback to publish the messages periodically.
    auto publish_msg = [this]() -> void {
        auto message = custom_interface::msg::MyName();

        std::cout << "Publishing My Initials: " << message.first_name << "." << message.last_name << "." << std::endl;

        this->my_initials_publisher_->publish(message);
      };
    // Finally send the message periodically.
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  rclcpp::Publisher<custom_interface::msg::MyName>::SharedPtr my_initials_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyInitialsPublisher>());
  rclcpp::shutdown();

  return 0;
}