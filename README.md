# vehicle_speed_tracker ROS 2 Package

Kerékfordulatszám alapú sebességmérő ROS 2 Humble környezetben

## Működési elv

A rendszer két független node-ból áll:
1. `wheel_speed_sensor_node`: 10 Hz frekvenciával adatokat generál a jármű négy kerekének percenkénti fordulatszámáról.
2. `vehicle_speed_calculator_node`: feliratkozik a kerékadatokra, kiszámítja azok átlagát, majd az adott keréksugárral meghatározza a jármű valós sebességét km/h-ban.

```mermaid
graph LR
    A[wheel_speed_sensor_node] -->|/wheel_speeds<br/>std_msgs/Float32MultiArray| B[vehicle_speed_calculator_node]
    B -->|/vehicle_speed_kmh<br/>std_msgs/Float32| C[(ros2 topic echo)]

