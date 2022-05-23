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
