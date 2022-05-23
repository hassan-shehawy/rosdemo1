# WORKSPACE
The workspace has a directory called src. Inside it, we have our packages. To create a package, while in the src directory type:
catkin_create_pkg package_name package_depend1 package_depend2 ...
For example: (to create a package called model_pks that depends on roscpp, rospy and std_msgs packages)
catkin_create_pkg model_pkg roscpp rospy std_msgs
# MODEL PACKAGE
This package is demonstrating the basics. To create a package, while in the src
## SAMPLE NODE IN C++
To create a node in c++, you have to write the source code (obviously in c++) and update the CMake file. Source code can be like:
#include <ros/ros.h>
#include <std_msgs/Float64.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "samplenode");
	ros::NodeHandle nh;
	ros::Publisher pub_obj = nh.advertise<std_msgs::Float64>("sample_topic",1);
	std_msgs::Float64 msg;
	msg.data=0;
	while(ros::ok)
	{
		msg.data+=0.01;
		pub_obj.publish(msg);
	}
} 
And CMake file:
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

## INTERACTION
hassan$roscore

hassan$rostopic list
/rosout
/rosout_agg

hassan$rosnode list
/rosout

hassan$rosrun model_pkg samplenode

hassan$rosnode list
/rosout
/samplenode

hassan$rostopic list
/rosout
/rosout_agg
/sample_topic 

hassan$rostopic info /sample_topic 
Type: std_msgs/Float64
Publishers: 
 * /samplenode (http://hassan-lenovo:33313/)
Subscribers: None

hassan$rosmsg show std_msgs/Float64
float64 data

hassan$rostopic hz /sample_topic 
subscribed to [/sample_topic]
average rate: 5268.091
	min: 0.000s max: 0.017s std dev: 0.00051s window: 4975
average rate: 5795.682
	min: 0.000s max: 0.017s std dev: 0.00042s window: 11293
average rate: 5687.014
	min: 0.000s max: 0.020s std dev: 0.00045s window: 16809
average rate: 5786.916
	min: 0.000s max: 0.020s std dev: 0.00044s window: 22982
average rate: 5718.775
	min: 0.000s max: 0.020s std dev: 0.00044s window: 27291

hassan$rostopic bw /sample_topic 
subscribed to [/sample_topic]
average: 32.34KB/s
	mean: 0.01KB min: 0.01KB max: 0.01KB window: 100
average: 56.85KB/s
	mean: 0.01KB min: 0.01KB max: 0.01KB window: 100
average: 42.06KB/s
	mean: 0.01KB min: 0.01KB max: 0.01KB window: 100
average: 1.26KB/s
	mean: 0.01KB min: 0.01KB max: 0.01KB window: 100

hassan$rostopic echo /sample_topic
data: 137.88
---
data: 137.89
---
data: 138.34
---
data: 138.35
---
data: 138.53
---
data: 138.54
---
data: 138.64
---
data: 138.65
---
data: 139.13
---
data: 139.14
---
data: 139.15
---
data: 139.18
---
data: 139.19
---
data: 139.28
---
data: 139.29
---
data: 139.45
---
data: 139.46
---
data: 139.63
---
data: 139.64
---
data: 139.76
---
data: 139.77



