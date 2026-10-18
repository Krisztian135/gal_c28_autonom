#include <memory>
#include <numeric>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "std_msgs/msg/float32.hpp"

class VehicleSpeedCalculatorNode : public rclcpp::Node
{
public:
  VehicleSpeedCalculatorNode()
  : Node("vehicle_speed_calculator_node")
  {
    // Feliratkozunk a szenzor adataira a /wheel_speeds topicon
    subscription_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "/wheel_speeds", 10,
      std::bind(&VehicleSpeedCalculatorNode::topic_callback, this, std::placeholders::_1));

    // Létrehozzuk a publishert a kiszamolt sebessegnek
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("/vehicle_speed_kmh", 10);

    RCLCPP_INFO(this->get_logger(), "VehicleSpeedCalculatorNode keszen all a szamolasra.");
  }

private:
  void topic_callback(const std_msgs::msg::Float32MultiArray::SharedPtr msg) const
  {
    if (msg->data.empty()) {
      return;
    }

    // 1. A kerekek RPM ertekeinek atlaga
    float sum_rpm = std::accumulate(msg->data.begin(), msg->data.end(), 0.0f);
    float avg_rpm = sum_rpm / msg->data.size();

    // 2. Kerek fizikai adatai (pl. standard r = 0.33 m kerek sugar)
    const float wheel_radius = 0.33f;
    const float pi = 3.14159265f;

    // Sebesseg keplet: kerulet * fordulat/perc * 60 / 1000 -> km/h
    float speed_kmh = (2.0f * pi * wheel_radius * avg_rpm * 60.0f) / 1000.0f;

    // 3. Eredmeny publikalasa
    auto out_msg = std_msgs::msg::Float32();
    out_msg.data = speed_kmh;
    publisher_->publish(out_msg);

    RCLCPP_INFO(this->get_logger(), "Atlag RPM: %.1f -> Jarmu sebesseg: %.2f km/h", avg_rpm, speed_kmh);
  }

  rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VehicleSpeedCalculatorNode>());
  rclcpp::shutdown();
  return 0;
}
