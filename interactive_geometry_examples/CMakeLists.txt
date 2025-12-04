cmake_minimum_required(VERSION 3.5)
project(interactive_geometry_examples)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(interactive_geometry_msgs REQUIRED)


add_executable(interactive_ellipsoid_client_node
  src/interactive_ellipsoid_client_node.cpp
)
ament_target_dependencies(interactive_ellipsoid_client_node
  rclcpp
  rclcpp_action
  interactive_geometry_msgs
)

# Install the executable(s)
install(TARGETS interactive_ellipsoid_client_node DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)

#ament_export_dependencies(rclcpp)
#ament_export_targets(interactive_ellipsoid_client_node HAS_LIBRARY_TARGET)
ament_package()

