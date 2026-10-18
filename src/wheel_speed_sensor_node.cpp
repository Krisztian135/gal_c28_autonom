#include <chrono>
#include <memory>
#include <vector>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

using namespace std::chrono_literals;

class WheelSpeedSensorNode : public rclcpp::Node
{
public:
  WheelSpeedSensorNode()
  : Node("wheel_speed_sensor_node"), count_(0.0)
  {
    // Létrehozzuk a publishert a /wheel_speeds topicra, 10-es puffer mérettel
    publisher_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("/wheel_speeds", 10);

    // 100 ms-onként (10 Hz) lefutó időzítő beállítása
    timer_ = this->create_wall_timer(
      100ms, std::bind(&WheelSpeedSensorNode::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "WheelSpeedSensorNode elindult, RPM adatok kuldese...");
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::Float32MultiArray();

    // Szimulált kerekek fordulatszáma (RPM): alapfordulatszám szinuszos ingadozással
    // Bal elso, jobb elso, bal hatso, jobb hatso kerekek
    float base_rpm = 600.0f + 100.0f * std::sin(count_);
    message.data = {
      base_rpm,
      base_rpm + 2.0f,
      base_rpm - 1.0f,
      base_rpm + 1.0f
    };

    count_ += 0.05f;

    // Uzenet publikalasa a topicra
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr publisher_;
  float count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<WheelSpeedSensorNode>());
  rclcpp::shutdown();
  return 0;
}
