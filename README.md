# ROS2 Beginner Tutorial

## Installing ROS2 on Ubuntu 20.04
Follow this ![link](http://docs.ros.org/en/humble/Installation/Alternatives/Ubuntu-Development-Setup.html) carefully and select Ubuntu 20.04 wherever it is necessary and install from source.

## Tutorials
- Follow these ![tutorial](http://docs.ros.org/en/humble/Tutorials.html) to understand the basics of ROS2. If you have installed the ROS2 from source, the ros2 setup path will be your 
```
. <installation_directory>/install/setup.bash
```
For convenience, you can append it to your bashrc, this will keep your underlay sourced whenever you open your terminal

- Source installation includess turtlesim and other packages.
- `colcon` can be installed by running the command:
```
sudo apt install python3-colcon-common-extensions
```

## Build Package and run Publisher-Subscriber
Follow along.
- Clone the repository in your ros2_ws/src folder. It should create beginner_tutorials folder in your /src.
- For ssh only 
```
git clone git@github.com:shelvinpauly/beginner_tutorials.git
```
Make sure that you source the current, if you did not update the bashrc
- Run the below commands:
```
cd beginner_tutorials
rosdep install -i --from-path src --rosdistro humble -y
cd ../.. # It should take your present working directory to <ROS2_workspace>
colcon build --packages-select cpp_pubsub
. install/setup.bash
ros2 run cpp_pubsub talker
```
- Open a new terminal, source the underlay 
```
. <ros2_installation_directory>/install/setup.bash
```
and then the overlay 
```
. install/setup.bash
```
- Run the subscriber
```
ros2 run cpp_pubsub listener
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
cppcheck --enable=all --std=c++17 src/cpp_pubsub/src/*.cpp --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unmatchedSuppression > ./results/cppcheck.txt
```
