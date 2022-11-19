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
ros2 run cpp_pubsub talker
```
- Open a new terminal
- Source it
- Run the subscriber
```
ros2 run cpp_pubsub listener
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

- Open a new terminal
- Source it
- Run the Subscriber
```
ros2 run ros2_cpp_pubsub param_listener
```
### Using a launch file to run the publisher, subscriber
- Type the below command to launch publisher and subscriber with default frequency (2Hz)
```
ros2 launch more_interfaces pub_sub_launch.yaml
```

```

## Using rqt_console to visualize the log messages:
Run the below command in a new terminal
```
ros2 run rqt_console rqt_console
```


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
