#include <ros/ros.h>

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "pullparam"); 
    ros::NodeHandle nh; 
    double pp,ii,dd;
    
    if (nh.getParam("/pid_gains/p", pp)) 
    {
       ROS_INFO("Proportional gain = %f",pp);
    }
    else
    {
       ROS_WARN("p gain value was not found in the parameter server");
    }
    if (nh.getParam("/pid_gains/i", ii)) 
    {
       ROS_INFO("Derivative gain = %f",ii);
    }
    else
    {
       ROS_WARN("i gain value was not found in the parameter server");
    }
    if (nh.getParam("/pid_gains/d", dd)) 
    {
       ROS_INFO("Integral gain = %f",dd);
    }
    else
    {
       ROS_WARN("d gain value was not found in the parameter server");
    }
}

