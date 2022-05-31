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
