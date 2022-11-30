cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/ChangeMyMessage.srv"
)

rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME}
"rosidl_typesupport_cpp" 
)

target_link_libraries(talker "${cpp_typesupport_target}")

ament_export_dependencies(rosidl_default_runtime)

install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})
  
install(DIRECTORY 
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
