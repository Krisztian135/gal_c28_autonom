from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='gal_c28_autonom',
            executable='wheel_speed_sensor_node',
            name='wheel_speed_sensor'
        ),
        Node(
            package='gal_c28_autonom',
            executable='vehicle_speed_calculator_node',
            name='vehicle_speed_calculator'
        )
    ])
