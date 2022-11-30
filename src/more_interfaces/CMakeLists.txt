cmake_minimum_required(VERSION 3.8)
project(more_interfaces)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

set(my_files
  "msg/MyName.msg"
  "msg/MyInitials.msg"
  "srv/MyInitials.srv"
  DEPENDENCIES std_msgs
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${my_files}
)

ament_export_dependencies(rosidl_default_runtime)

add_executable(server src/initials_server.cpp)
ament_target_dependencies(server
  "rclcpp"
  
)

add_executable(client src/initials_client.cpp)
ament_target_dependencies(client
  "rclcpp"
  
)

install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})

add_executable(publish_my_initials
  src/publish_my_initials.cpp
)

add_executable(subscribe_my_initials
  src/subscribe_my_initials.cpp
)

#add_executable(server src/initials_server.cpp)
#ament_target_dependencies(server
#rclcpp moree_interfaces)

ament_target_dependencies(publish_my_initials
  "rclcpp"
  std_msgs
)

ament_target_dependencies(subscribe_my_initials
  "rclcpp"
  std_msgs
)

ament_export_dependencies(rosidl_default_runtime)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS publish_my_initials
 DESTINATION lib/${PROJECT_NAME})

install(TARGETS subscribe_my_initials
 DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

target_link_libraries(publish_my_initials "${cpp_typesupport_target}")

target_link_libraries(subscribe_my_initials "${cpp_typesupport_target}")





if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
