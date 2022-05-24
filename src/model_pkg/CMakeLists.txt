cmake_minimum_required(VERSION 3.0.2)
project(model_pkg)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  	     roscpp
  	     rospy
  	     std_msgs)

###################################
## catkin specific configuration ##
###################################
catkin_package()

###########
## Build ##
###########
include_directories(${catkin_INCLUDE_DIRS})

add_executable(samplenode src/samplenode.cpp)
target_link_libraries(samplenode ${catkin_LIBRARIES})

add_executable(samplesub src/samplesub.cpp)
target_link_libraries(samplesub ${catkin_LIBRARIES})