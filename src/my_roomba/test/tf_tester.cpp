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
 * @date 2022-12-5
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// #include <gtest/gtest.h>
// #include <stdlib.h>
// #include <rclcpp/rclcpp.hpp>

// #include "geometry_msgs/msg/transform_stamped.hpp"

// class TestNode : public testing::Test {
//  protected:
//   rclcpp::Node::SharedPtr node_;
// };

// TEST_F(TestNode, test_for_publishers) {
//   node_ = std::make_shared<rclcpp::Node>("static_transform_publisher");
//   //geometry_msgs::msg::TransformStamped t;
//   auto test_publisher = node_->create_publisher<geometry_msgs::msg::TransformStamped>
//                     ("chatter", 10.0);

// //   auto num_of_publishers = node_->t("chatter");
//   EXPECT_EQ("world", test_publisher->header);
// }


// int main(int argc, char** argv) {
//   rclcpp::init(argc, argv);
//   ::testing::InitGoogleTest(&argc, argv);
//   int result = RUN_ALL_TESTS();
//   rclcpp::shutdown();
//   return result;
// }


#include <gtest/gtest.h>
#include <stdlib.h>
#include <rclcpp/rclcpp.hpp>

#include "std_msgs/msg/string.hpp"

/**
 * @brief Class TestNode
 * 
 */
class TestNode : public testing::Test {
 protected:
  rclcpp::Node::SharedPtr node_;
};

/**
 * @brief Construct a new test f object which tests the number of publishers
 * 
 */
TEST_F(TestNode, test) {
  node_ = std::make_shared<rclcpp::Node>("test_num_publish");

  auto test_num_publish = node_->create_publisher<std_msgs::msg::String>
                    ("chatter", 10.0);

  auto num = node_->count_publishers("chatter");
  EXPECT_EQ(1, static_cast<int>(num));
}

/**
 * @brief Main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  rclcpp::shutdown();
  return result;
}