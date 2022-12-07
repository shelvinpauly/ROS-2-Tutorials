from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition

def generate_launch_description():
    
    record = LaunchConfiguration('record_all')

    return LaunchDescription([

        DeclareLaunchArgument(
            'record_all',
            default_value='True'
        ),

        Node(
            package='cpp_pubsub',
            executable='talker'
        ),

        ExecuteProcess(
        condition=IfCondition(record),
        cmd=[
            'ros2', 'bag', 'record', '-o my_bag', '-a'
        ],
        shell=True
        )

    ])