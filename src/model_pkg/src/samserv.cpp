#include <ros/ros.h>
#include <model_pkg/samserv.h>
#include <iostream>
#include <string>
using namespace std;

bool statcb(model_pkg::samservRequest& req, model_pkg::samservResponse& res)
{
    ROS_INFO("Now inside the callback");
    string inqstat(req.status); 
    res.camonoff=false;
    if (inqstat.compare("init")==0)
    {
        ROS_INFO("Checking Initialization");
        res.procid = 15;
        res.camonoff=false;
        res.desc="Moving the robot to initial ready pose";
    } 
     if (inqstat.compare("load")==0)
    {
        ROS_INFO("Checking loading process");
        res.procid = 35;
        res.camonoff=true;
        res.desc="Begin the loading process";
    }    
    
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sampserv");
  ros::NodeHandle nh;

  ros::ServiceServer serv = nh.advertiseService("checkstatus", statcb);
  ROS_INFO("Waiting for an inquiry of the status ...");
  ros::spin();

  return 0;
}
