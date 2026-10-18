cmake_minimum_required(VERSION 3.8)
project(gal_c28_autonom)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Fuggosegek betoltese
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 1. Node leforditasa (Sensor)
add_executable(wheel_speed_sensor_node src/wheel_speed_sensor_node.cpp)
ament_target_dependencies(wheel_speed_sensor_node rclcpp std_msgs)

# 2. Node leforditasa (Calculator)
add_executable(vehicle_speed_calculator_node src/vehicle_speed_calculator_node.cpp)
ament_target_dependencies(vehicle_speed_calculator_node rclcpp std_msgs)

# Futtathato allomanyok elhelyezese a csomag konyvtaraban
install(TARGETS
  wheel_speed_sensor_node
  vehicle_speed_calculator_node
  DESTINATION lib/${PROJECT_NAME}
)

# Launch mappa telepitve legyen, ha keszitunk launch fajlt
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
  OPTIONAL
)

ament_package()
