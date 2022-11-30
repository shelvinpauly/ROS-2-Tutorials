cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/ChangeMyMessage.srv"
)

add_executable(static_transform_publisher src/publisher_member_function.cpp)
ament_target_dependencies(
  static_transform_publisher
  geometry_msgs
  rclcpp
  std_msgs
  tf2
  tf2_ros
)

target_link_libraries(static_transform_publisher "${cpp_typesupport_target}")
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME}
"rosidl_typesupport_cpp" 
)

#add_executable(listener src/subscriber_member_function.cpp)
#ament_target_dependencies(listener rclcpp std_msgs)
#rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME}
#"rosidl_typesupport_cpp" 
#)

target_link_libraries(static_transform_publisher "${cpp_typesupport_target}")
ament_export_dependencies(rosidl_default_runtime)

install(TARGETS
  static_transform_publisher
  DESTINATION lib/${PROJECT_NAME})
  
install(DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()