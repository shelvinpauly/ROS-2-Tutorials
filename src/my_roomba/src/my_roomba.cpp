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
 * @date 2022-12-7
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <geometry_msgs/msg/twist.hpp>

// Using literals to the sensor messages types for more readability
using std::placeholders::_1;
using namespace std::chrono_literals;

// using LIDAR = sensor_msgs::msg::LaserScan;
// using TWIST = geometry_msgs::msg::Twist;

/**
 * @brief Class to do slam for my_roomba
 * 
 */
class AutoRoomba : public rclcpp::Node {
 public:
 /**
  * @brief Create an object to intiate my_roomba
  * 
  */
    AutoRoomba() :
        Node("roomba") {
            // Initialize the publisher and subscriber
            auto callback = std::bind(&AutoRoomba::callback, this, _1);
            sub_lidar = this->create_subscription<sensor_msgs::msg::LaserScan>
                                        ("scan", 10, callback);
            pub_velocity = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        }

 private:
 /**
  * @brief Callback function for the lidar scan
  * 
  * @param msg 
  */
    void callback(const sensor_msgs::msg::LaserScan& msg) {
        if (msg.header.stamp.sec == 0) {
            return;
        }
        auto scan_data = msg.ranges;
        auto start_angle = 330;
        auto angle_range = 60;
        for (int i = start_angle; i < start_angle + angle_range; i++) {
            if (scan_data[i % 360] < 2) {
                move(0.0, 0.3);
            } else {
                move(0.1, 0.0);
            }
        }
    }
    /**
     * @brief Function to publish velocities in x and z directions.
     * 
     * @param x_velocity 
     * @param z_velocity 
     */
    void move(float x_velocity, float z_velocity) {
        auto velocity = geometry_msgs::msg::Twist();
        velocity.linear.x = x_velocity;
        velocity.angular.z = -z_velocity;
        pub_velocity->publish(velocity);
    }

    // Private class members
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_lidar;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_velocity;
    rclcpp::TimerBase::SharedPtr m_timer;
    sensor_msgs::msg::LaserScan m_last_data;
};

/**
 * @brief Main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AutoRoomba>());
    rclcpp::shutdown();
    return 0;
}
