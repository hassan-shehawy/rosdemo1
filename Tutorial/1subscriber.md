# SAMPLE SUBSCRIBER IN C++
To create a subscriber in c++, you have to write the source code (obviously in c++) and update the CMake file. Source code can be like:
#include <ros/ros.h>
#include <std_msgs/Float64.h>

void sample_callback(const std_msgs::Float64& sample_msg)
{
	ROS_INFO("Message scaled by 10 = %f", sample_msg.data * 10);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "samplesub");
	ros::NodeHandle nh;
	ros::Subscriber sub_obj = nh.subscribe("sample_topic",1, sample_callback);
	ros::spin();
	return 0;
} 
And update the CMake file by adding:
add_executable(samplesub src/samplesub.cpp)
target_link_libraries(samplesub ${catkin_LIBRARIES})

## INTERACTION
hassan$rosrun model_pkg samplenode

hassan$rostopic echo /sample_topic
data: 0.02
---
data: 0.03
---
data: 0.04
---
data: 0.05
---
data: 0.06
---

hassan$rosrun model_pkg samplesub 
[ INFO] [1653385917.759245931]: Message scaled by 10 = 0.200000
[ INFO] [1653385918.758980299]: Message scaled by 10 = 0.300000
[ INFO] [1653385919.759079044]: Message scaled by 10 = 0.400000

hassan$rosnode list
/rosout
/samplenode
/samplesub


