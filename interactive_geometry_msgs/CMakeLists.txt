cmake_minimum_required(VERSION 3.5)
project(interactive_geometry_msgs)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclpy REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

rosidl_generate_interfaces(
  ${PROJECT_NAME}
  "msg/Ellipsoid.msg"
  "action/InteractiveEllipsoid.action"
  DEPENDENCIES geometry_msgs)

# Ament package settings
ament_export_dependencies(
  rclpy
  geometry_msgs
  rosidl_default_runtime
  std_msgs)
ament_package()
