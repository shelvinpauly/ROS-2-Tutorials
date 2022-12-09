from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, PythonExpression
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import IfCondition

from ament_index_python.packages import get_package_share_directory

import os

def generate_launch_description():

    flag = LaunchConfiguration('record')

    return LaunchDescription([

        DeclareLaunchArgument(
            'record',
            default_value='False'
        ),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('turtlebot3_gazebo'), 'launch'),
            '/turtlebot3_world.launch.py'])
        ),

        Node(
            package='my_roomba',
            executable='roomba',
        ),

        ExecuteProcess(
        condition=IfCondition(flag),
        cmd=[
            'ros2', 'bag', 'record', '-o roomba_bag', '-a', '-x "/camera.+"'
        ],
        shell=True
        )

    ])