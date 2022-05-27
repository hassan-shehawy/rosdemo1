#include <ros/ros.h>
#include <model_pkg/samsg.h>
#include <math.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "samcustmsgpub");
	ros::NodeHandle nh;
	ros::Rate sleeper(1);
	ros::Publisher pub_obj = nh.advertise<model_pkg::samsg>("sample_topic_customsg",1);
	model_pkg::samsg  custmsg;

	custmsg.header.stamp = ros::Time::now(); 
	custmsg.header.seq=0; 
	custmsg.header.frame_id = "base";
	custmsg.samint= 7;
	custmsg.samfrac=21.4;
	custmsg.samstring="hassan";
	double sqrt_arg;

	while (ros::ok()) 
	{
		custmsg.header.seq++; 
		custmsg.header.stamp = ros::Time::now(); 
		custmsg.samint+=5; 
		sqrt_arg = custmsg.samfrac;
		custmsg.samfrac = sqrt(sqrt_arg);
  
		pub_obj.publish(custmsg); 
		sleeper.sleep(); 
	}
} 
