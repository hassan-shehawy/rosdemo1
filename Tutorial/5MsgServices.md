# CUSTOM MESSAGE
Note: There exists some primitive data types that we use to build a custom message
1. Define the message structure in a .msg file in a "msg" directory
2. Edit the CMake and package.xml files
3. Compile using catkin_make you get a header file in devel/include directory
4. Make a publisher node that can publish this customized message type


# SERVICES
## Communication happens in 3 ways:
1. Publisher/Subscriber
2. Client/Service (blocked) 
3. ActionClient/ActionServer
## Core Concepts:
1. Directory called srv in which we have srv files
2. Package XML file needs to be edited as the case with custom message
3. CMake file also needs to have the add_service_files() and generate_messages() lines 
4. Also here, compiling generates a header file in devel/include directory
5. You can interact with the service manually on the command line or by using code 
## .srv files
Data type for request and response, a file could be something like:
string status
---
bool camonoff
int32 procid
string desc
## cpp service node
A sample code could be:
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
## compiling
As usual add the lines:
add_executable(samserv src/samserv.cpp)
target_link_libraries(samserv ${catkin_LIBRARIES})
## interactig
rosrun model_pkg samserv 
[ INFO] [1653995703.284036954]: Waiting for an inquiry of the status ...
rosservice call /checkstatus "status: 'init'"
camonoff: False
procid: 15
desc: "Moving the robot to initial ready pose"
On the other terminal:
[ INFO] [1653995768.086329007]: Now inside the callback
[ INFO] [1653995768.086425415]: Checking Initialization
rosservice call /checkstatus 'load'
camonoff: True
procid: 35
desc: "Begin the loading process"
On the other terminal:
[ INFO] [1653995986.008986729]: Now inside the callback
[ INFO] [1653995986.009079869]: Checking loading process


# CLIENT
This is how we interact with a service using code. So, a cpp file can be written as:
#include <ros/ros.h>
#include <model_pkg/samserv.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "samclient");
    ros::NodeHandle nh;
    ros::ServiceClient clnt = nh.serviceClient<model_pkg::samserv>("checkstatus");
    model_pkg::samserv serv;
    bool camonoff = false;
    string inqstat;
    while (ros::ok()) 
    {
        std::cout<<endl;
        std::cout<<"Specify a process (q to quit): ";
        std::cin>>inqstat;
        if (inqstat.compare("q")==0)
            return 0;
        serv.request.status = inqstat; 
        if (clnt.call(serv)) 
        {                
            std::cout << serv.request.status << " process includes: " << serv.response.desc << std::endl;
            std::cout << "This process has an ID = " << serv.response.procid << std::endl;
            if (serv.response.camonoff) 
            {

                std::cout << "The camera is turned ON" << std::endl;
            } 
            else 
              {
                std::cout << "The camera is turned ON" << std::endl;
              }
        } 
        else 
          {
            ROS_ERROR("Failed to call the service checkstat");
            return 1;
          }
    }
    return 0;
}
## compiling
As usual add the lines:
add_executable(samclient src/samclient.cpp)
target_link_libraries(samclient ${catkin_LIBRARIES})
## interactig
rosrun model_pkg samserv
rosrun model_pkg samclient 

Specify a process (q to quit): init
init process includes: Moving the robot to initial ready pose
This process has an ID = 15
The camera is turned ON

Specify a process (q to quit): load
load process includes: Begin the loading process
This process has an ID = 35
The camera is turned ON

Specify a process (q to quit): init
init process includes: Moving the robot to initial ready pose
This process has an ID = 15
The camera is turned ON

Specify a process (q to quit): load
load process includes: Begin the loading process
This process has an ID = 35
The camera is turned ON

Specify a process (q to quit): q

