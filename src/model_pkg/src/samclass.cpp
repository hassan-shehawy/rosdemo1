#include "samclass.h"


// Using the constructor to initialize the member data (univvar) and call the member functions
// Note that it is a 1-arg constructor (needs a pointer to a NodeHandle variable)
samclass::samclass(ros::NodeHandle* nhp):nh(*nhp)
{ 
    ROS_INFO("Now in the samclass class constructor");
    initsub(); 
    initpub();
    univvar = 0.0; 
}

void samclass::initsub()
{
    ROS_INFO("Initializing Subscribers");
    samsub = nh.subscribe("samintopic", 1, &samclass::subcb, this);  
}

void samclass::initpub()
{
    ROS_INFO("Initializing Publishers");
    sampub = nh.advertise<std_msgs::Float32>("samoptopic", 1, true); 
}

void samclass::subcb(const std_msgs::Float32& sample_msg) 
{
    globvar = sample_msg.data; 
    ROS_INFO("Now in callback function, I received this: %f",globvar);
    std_msgs::Float32 opmsg;
    univvar += globvar; 
    opmsg.data = univvar;
    sampub.publish(opmsg); 
}

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "samclass"); 
    ros::NodeHandle nh; 

    ROS_INFO("Now in main() instantiating an object of type samclass");

    samclass samobj(&nh);  

    ROS_INFO("Now in main() proceeding to  spin()");

    ros::spin();
    
    return 0;
} 