cmake_minimum_required(VERSION 3.8)
project(my_ros2_projects)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(cpp_first_node_oop src/my_first_cpp_oop_node.cpp)
ament_target_dependencies(cpp_first_node_oop rclcpp)
add_executable(robot_news_station_PUB src/robot_news_station_PUB.cpp)
ament_target_dependencies(robot_news_station_PUB rclcpp example_interfaces)
add_executable(robot_news_station_SUB src/robot_news_station_SUB.cpp)
ament_target_dependencies(robot_news_station_SUB rclcpp example_interfaces)
add_executable(Actv02_Node1_Pub src/Actv02_Node1_Pub.cpp)
ament_target_dependencies(Actv02_Node1_Pub rclcpp example_interfaces)
add_executable(Actv02_Node2_Sub_Pub src/Actv02_Node2_Sub&Pub.cpp)
ament_target_dependencies(Actv02_Node2_Sub_Pub rclcpp example_interfaces)
add_executable(add_two_ints_client_NoOOP src/add_two_ints_client_NoOOP.cpp)
ament_target_dependencies(add_two_ints_client_NoOOP rclcpp example_interfaces)
add_executable(add_two_ints_server src/add_two_ints_server.cpp)
ament_target_dependencies(add_two_ints_server rclcpp example_interfaces)
add_executable(add_two_ints_client_OOP src/add_two_ints_client_OOP.cpp)
ament_target_dependencies(add_two_ints_client_OOP rclcpp example_interfaces)
add_executable(Actv03_Node2_Sub_Pub_Srv src/Actv03_Node2_Sub&Pub&Srv.cpp)
ament_target_dependencies(Actv03_Node2_Sub_Pub_Srv rclcpp example_interfaces)
add_executable(Actv03_Node1_Pub_Client src/Actv03_Node1_Pub&Client.cpp)
ament_target_dependencies(Actv03_Node1_Pub_Client rclcpp example_interfaces)

install(TARGETS
  cpp_first_node_oop
  robot_news_station_PUB
  robot_news_station_SUB
  Actv02_Node1_Pub
  Actv02_Node2_Sub_Pub
  add_two_ints_client_NoOOP
  add_two_ints_server
  add_two_ints_client_OOP
  Actv03_Node2_Sub_Pub_Srv
  Actv03_Node1_Pub_Client
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
