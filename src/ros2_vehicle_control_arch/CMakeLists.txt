cmake_minimum_required(VERSION 3.8)
project(ros2_vehicle_control_arch)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(vehconarch_interfaces REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(DriverNode src/DriverNode.cpp)
ament_target_dependencies(DriverNode rclcpp vehconarch_interfaces)
add_executable(VehicleControlManager src/VehicleControlManager.cpp)
ament_target_dependencies(VehicleControlManager rclcpp vehconarch_interfaces std_msgs)
add_executable(SteeringControlNode src/SteeringControlNode.cpp)
ament_target_dependencies(SteeringControlNode rclcpp vehconarch_interfaces std_msgs)
add_executable(SpeedControlNode src/SpeedControlNode.cpp)
ament_target_dependencies(SpeedControlNode rclcpp vehconarch_interfaces std_msgs)


install(TARGETS
  DriverNode
  VehicleControlManager
  SteeringControlNode
  SpeedControlNode
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
