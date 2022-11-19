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
```
git clone https://github.com/okritvik/beginner_tutorials.git
```
Make sure that your terminal is sourced
- Run the below commands:
```
cd beginner_tutorials
rosdep install -i --from-path src --rosdistro humble -y
cd ../.. # It should take your present working directory to <ROS2_workspace>
colcon build
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
ros2 run ros2_cpp_pubsub talker
```
- Open a new terminal
- Source it
- Run the subscriber
```
ros2 run ros2_cpp_pubsub listener
```

## Run Server, Client-Publisher, Subscriber
Follow the below instructions to run the simple server, client, publisher and subscriber.
- Run the publisher
```
ros2 run ros2_cpp_pubsub server
```
- Open a new terminal
- Source it
- Run the client-publisher
```
ros2 run ros2_cpp_pubsub client_pub
```
- Open a new terminal
- Source it
- Run the subscriber
```
ros2 run ros2_cpp_pubsub client_sub
```
- These nodes use /server_data as a topic
- Service name is ```change_string```
- To check the server response (without running the publisher and subscriber) please use the command in a new terminal:
```
ros2 service call /change_strings ros2_cpp_pubsub/srv/ChangeString "{input: 'Hello world'}"
```
Note that the server should be running and new terminal should be sourced to execute the above command.

## Run Publisher and Subscriber using Parameters
Follow the below instructions to run the simple publisher and subscriber that uses parameters to change publishing frequency with different log levels.
- Run the publisher
```
ros2 run ros2_cpp_pubsub param_talker
```
This node uses ```/chatter``` topic with a parameter name "frequency" of type double. Default value is 2.0 (Hz). <br>
To change the frequency, use the below command in a new terminal:
```
ros2 param set /param_publisher frequency <frequency value (double)>
```
example:
```
ros2 param set /param_publisher frequency <5.0>
```
- Open a new terminal
- Source it
- Run the Subscriber
```
ros2 run ros2_cpp_pubsub param_listener
```
### Using a launch file to run the publisher, subscriber
- Type the below command to launch publisher and subscriber with default frequency (2Hz)
```
ros2 launch ros2_cpp_pubsub pub_sub_launch.yaml
```
To set a different frequency, open a new terminal and run the below command:
```
ros2 param set /param_publisher frequency <frequency value (double)>
```
example:
```
ros2 param set /param_publisher frequency <5.0>
```
- Type the below command to launch publisher and subscriber with user defined frequency
```
ros2 launch ros2_cpp_pubsub pub_sub_launch.yaml frequency:=<user defined frequency (double)>
```
example:
```
ros2 launch ros2_cpp_pubsub pub_sub_launch.yaml frequency:=501.0
```

## Using rqt_console to visualize the log messages:
Run the below command in a new terminal
```
ros2 run rqt_console rqt_console
```

## Issues encountered
- Some nodes might not output anything in the terminal. Hence, before running the executable node, please run the below two commands
```
export RCUTILS_LOGGING_USE_STDOUT=0
export RCUTILS_LOGGING_BUFFERED_STREAM=0
```
- To force the color coding in the terminal to view different log levels, use the below export command in the terminal
```
export RCUTILS_COLORIZED_OUTPUT=1  # 1 for forcing color coding
```
- The default logger level is INFO. To change it for a node like param_publisher (param_talker executable), run the below command:
```
ros2 run ros2_cpp_pubsub param_talker --ros-args --log-level debug
```
- I have yet to figure out using --ros-args in the YAML launch file.


## Static Code Analysis
### cpplint
Run the below command from inside the package folder `beginner_tutorials`
```
cpplint --filter=-build/c++11,+build/c++17,-build/namespaces,-build/include_order src/*.cpp &> ./results/cpplint.txt
```
### cppcheck
Run the below command from the project root folder `beginner_tutorials`
```
cppcheck --enable=all --std=c++17 src/*.cpp --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unmatchedSuppression > ./results/cppcheck.txt
