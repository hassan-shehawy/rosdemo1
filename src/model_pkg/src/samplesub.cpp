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