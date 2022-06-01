#include<ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include<model_pkg/samactAction.h>

void servdone(const actionlib::SimpleClientGoalState& stat, const model_pkg::samactResultConstPtr& reslt) 
{
    ROS_INFO(" Inside the servdone callback: server response is: [%s]", stat.toString().c_str());
    int diff = reslt->output - reslt->goal_stamp;
    ROS_INFO("the received result output = %d while the goal_stamp = %d and the difference = %d", reslt->output, reslt->goal_stamp, diff);
}

int main(int argc, char** argv) 
{
    ros::init(argc, argv, "sampactclient"); 
    int g_count = 0;
    model_pkg::samactGoal gl;
    actionlib::SimpleActionClient<model_pkg::samactAction> action_client("sample_act", true);

    ROS_INFO("waiting for server: ");

    bool server_exists = action_client.waitForServer(ros::Duration(5.0)); 

    if (!server_exists) 
    {
        ROS_WARN("Server connection did not happen!");
        return 0; 
    }

    ROS_INFO("Server connection happened!");

    while (true) 
    {
        g_count++;
        gl.input = g_count; 
        action_client.sendGoal(gl, &servdone); 
        bool finished_before_timeout = action_client.waitForResult(ros::Duration(5.0));
        if (!finished_before_timeout) 
        {
            ROS_WARN("Timeout! This goal took too long: %d", g_count);
            return 0;
        } 
        else 
        {
            ROS_INFO("We have something!");
        }
    }

    return 0;
}
