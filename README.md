# ROS2 Beginner Tutorial
This package is tested on ROS2 Humble. If you have ROS2 Humble already installed, please skip the installation steps.
## Installing ROS2 on Ubuntu 22.04
Follow this ![link](http://docs.ros.org/en/humble/Installation/Alternatives/Ubuntu-Install-Binary.html) to install ROS2 Humble on your new Ubuntu 22.04 Desktop (binary installation).
## Installing ROS2 on Ubuntu 20.04
Follow this ![link](http://docs.ros.org/en/humble/Installation/Alternatives/Ubuntu-Development-Setup.html) carefully and select Ubuntu 20.04 wherever it is necessary and install from source.
## Tutorials
- Follow these ![tutorial](http://docs.ros.org/en/humble/Tutorials.html) to understand the basics of ROS2. If you have installed the ROS2 from source, the ros2 setup path will be your 
```
. <installation directory>/install/setup.bash
```
- Source installation installs turtlesim and other packages. No need to use the commands listed in the above tutorial. 
- `colcon` can be installed by running the command:
```
sudo apt install python3-colcon-common-extensions
```

## Clone and Build the package
- Clone this repository in your ROS2 Workspace /src folder. It should create beginner_tutorials folder in your /src.

Make sure that your terminal is sourced
- Run the below commands:
```
cd beginner_tutorials
rosdep install -i --from-path src --rosdistro humble -y
cd ../.. # It should take your present working directory to <ROS2_workspace>
colcon build --packages-select cpp_pubsub
. install/setup.bash
```

## Commands to source a new Terminal window
- When a new terminal is opened, please source your terminal using
```
. <ros2_installation_directory>/install/setup.bash
. install/setup.bash
```

## Run Publisher-Subscriber
Follow the below instructions to run the simple publisher and subscriber package.
- Run the publisher
```
ros2 run cpp_pubsub talker
```
- Open a new terminal
- Source it
- Run the subscriber
```
ros2 run cpp_pubsub listener
```

## Run the Custom service change_message
Follow the below instructions to run the simple server, client, publisher and subscriber.
- Run the publisher
```
ros2 run cpp_pubsub talker
```
- Open a new terminal
- Source it
- Call the service /change_message
```
ros2 service call /change_message cpp_pubsub/srv/ChangeMyMessage "{in_string: Attention}"
```
### Using a launch file to run the publisher, subscriber with and without parameter
- Type the below command to launch publisher and subscriber with default frequency (5Hz)
```
ros2 launch cpp_pubsub my_custom_launch.yaml
```
- Type the below command to launch publisher and subscriber with new frequency (10Hz)
```
ros2 launch cpp_pubsub my_custom_launch.yaml new_freq:=10.0
```

### Logging
- Debug (At the beginning of publisher)
```
ros2 launch cpp_pubsub my_custom_launch.yaml
```
- Error Log
```
ros2 launch cpp_pubsub my_custom_launch.yaml new_freq:=-10.0
```
- Warn and Fatal Log
```
ros2 launch cpp_pubsub my_custom_launch.yaml new_freq:=0.0
```

## Using rqt_console to visualize the log messages:
Run the below command in a new terminal
```
ros2 run rqt_console rqt_console
```

## Static code analysis
Navigate to cpp_pubsub package and then run
```
cd src/beginner_tutorials/src/cpp_pubsub/
```

### Cpplint
```
cpplint --filter=-build/c++11,+build/c++17,-build/namespaces,-build/include_order src/*.cpp &> ../results/cpplint.txt
```
### Cppcheck
```
cppcheck --enable=all --std=c++17 src/*.cpp --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unmatchedSuppression > ../results/cppcheck.txt
