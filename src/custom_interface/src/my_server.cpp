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
 * @file my_server.cpp
 * @author Shelvin Pauly (spauly@umd.edu)
 * @brief A server that manipulates the string input from client
 * @version 0.1
 * @date 2022-11-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "rclcpp/rclcpp.hpp"
#include "custom_interface/srv/initials.hpp"
#include "custom_interface/msg/my_name.hpp"

#include <memory>
#include <string>

// Typedefs declared by using to improve code readability

using my_data = custom_interface::msg::MyName;
using REQUEST = std::shared_ptr
                <custom_interface::srv::Initials::Request>;
using RESPONSE = std::shared_ptr
                <custom_interface::srv::Initials::Response>;

using NODE = rclcpp::Node;

using SERVICE = custom_interface::srv::Initials;

/**
 * @brief This function manipulates the input from client request
 * 
 * @param request Given by the client
 * @param response Given by the server to the client
 */
void manipulate(const REQUEST request, RESPONSE response) {
    auto input_str1 = static_cast<std::string>(request->first_name.c_str());
    auto input_str2 = static_cast<std::string>(request->last_name.c_str());
    auto add_str = input_str1[0] + input_str2[0];
    response->inits = add_str;
    // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\n %s",
    //             request->input.c_str());
    // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response:
    // [%s, %s]", response->output.c_str(), "Modified");
}

/**
 * @brief This function initializes the server with a node and service name
 * 
 * @param argc 
 * @param argv 
 * @return int 0
 */
int main(int argc, char **argv) {
    // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "%d", argc);
    rclcpp::init(argc, argv);

    std::shared_ptr<NODE> node = NODE::make_shared("string_server");

    rclcpp::Service<SERVICE>::SharedPtr service =
                node->create_service<SERVICE>("change_strings",  &manipulate);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to change string");

    rclcpp::spin(node);
    rclcpp::shutdown();
}