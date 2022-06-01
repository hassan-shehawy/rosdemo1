#include<ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include<model_pkg/samactAction.h>

int goal_count = 0;
bool counter_fail = false;

class sampactserv 
{
private:

    ros::NodeHandle nh;  
    actionlib::SimpleActionServer<model_pkg::samactAction> as;

    model_pkg::samactGoal gl; 
    model_pkg::samactResult reslt; 
    model_pkg::samactFeedback fdbk; 

public:
    sampactserv(); 
    ~sampactserv(void) {}
    void actcb(const actionlib::SimpleActionServer<model_pkg::samactAction>::GoalConstPtr& goal);
};

sampactserv::sampactserv():as(nh, "sample_act", boost::bind(&sampactserv::actcb, this, _1),false) 
{
    ROS_INFO("Now inside the constructor ...");
    as.start(); 
}

void sampactserv::actcb(const actionlib::SimpleActionServer<model_pkg::samactAction>::GoalConstPtr& goal) 
{
    ROS_INFO("Now inside the callback ");
    ROS_INFO("The goal value = %d", goal->input);

    goal_count++; 
    reslt.output = goal_count; 
    reslt.goal_stamp = goal->input;

    if (goal_count != goal->input) 
    {
        ROS_WARN("MISMATCH!");
        ROS_INFO("goal_count = %d; goal_stamp = %d", goal_count, reslt.goal_stamp);
        counter_fail = true; 
        ROS_WARN("Aborting goal ... ");
        as.setAborted(reslt); 
    }
    else 
    {
         as.setSucceeded(reslt);
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "sampactservr"); 

    sampactserv as_obj; 

    ROS_INFO("Now in main()");

    while (!counter_fail && ros::ok()) 
   { 
        ros::spinOnce(); 
   }

    return 0;
}

