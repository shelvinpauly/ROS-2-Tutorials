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

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/srv/my_initials.hpp"

#include<string>
#include <memory>

void initialize(const std::shared_ptr<more_interfaces::srv::my_initials::Request> request,
          std::shared_ptr<more_interfaces::srv::my_initials::Response> response)
{
  response->initials = request->first + request->last;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %s" " b: %s",
                request->first, request->last);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%s]", (std::string)response->inits);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("initials_server");

  rclcpp::Service<more_interfaces::srv::my_initials>::SharedPtr service =
    node->create_service<more_interfaces::srv::my_initials>("initials", &initialize);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to generate the initials.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}