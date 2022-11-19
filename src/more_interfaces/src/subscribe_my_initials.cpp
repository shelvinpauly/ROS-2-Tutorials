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

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
// Include the header of our newly created MyName.msg
#include "more_interfaces/msg/my_name.hpp"

using std::placeholders::_1;

class MyInitialsSubscriber : public rclcpp::Node {
 public:
  MyInitialsSubscriber()
  : Node("my_initials_subscriber") {
    // Create a callback to publish the messages periodically.
    my_initials_subscriber =
      this->create_subscription<more_interfaces::msg::MyName>("my_initials", 10,  std::bind(&MyInitialsSubscriber::topic_callback, this, _1));
  }

 private:
  void topic_callback(const more_interfaces::msg::MyName & msg) const {
    RCLCPP_INFO(this->get_logger(), "Shelvin heard: '%s'", msg.first_name.c_str());
  }
  rclcpp::Subscription<more_interfaces::msg::MyName>::SharedPtr my_initials_subscriber;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MyInitialsSubscriber>());
  rclcpp::shutdown();
  return 0;
}
