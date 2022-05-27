#ifndef EXAMPLE_ROS_CLASS_H_
#define EXAMPLE_ROS_CLASS_H_

#include <ros/ros.h> 
#include <std_msgs/Float32.h>

class samclass
{
public:
	//The constructor
	samclass(ros::NodeHandle* nhp);
private:
	//Member Data
	//1. Objects
	ros::NodeHandle nh; 	
    ros::Subscriber samsub; 
    ros::Publisher  sampub;
    //2. Variables
    double globvar; 
    double univvar; 

    //Member Functions
    void initsub(); 
    void initpub();    
    void subcb(const std_msgs::Float32& sample_msg); 
};

#endif 