# Action Server - Action Client
This is the third type of communication. To make it happen, you need to do the following:
1. Define the action file (in a folder named action, make .action files)
2. Edit the CMake and package.xml files
3. Compile using catkin_make you get a header files in devel/include directory
4. Make nodes that interact with this communication

# VERY IMPORTANT NOTE
To save yourself a lot of hassle, first compile to get the header files for your custom messages/services/actions WITHOUT any relevant nodes (comment the add_executable lines in the CMake file), source devel/setup.bash and THEN you can add the nodes for compilations.

# ACTION FILES
It must have 3 sections like:
#goal 
int32 input
---
#result 
int32 output
int32 goal_stamp
---
#feedback
int32 fdbk
## cpp action node
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
## compiling
add_executable(sampactclient src/sampactclient.cpp)
target_link_libraries(sampactclient ${catkin_LIBRARIES})
## interactig
### Run only client:
rosrun model_pkg sampactclient 
[ INFO] [1654097954.415688255]: waiting for server: 
[ WARN] [1654097959.416507080]: Server connection did not happen!
### Run server then client
rosrun model_pkg sampactservr 
[ INFO] [1654097832.215531795]: Now inside the constructor ...
[ INFO] [1654097832.222882701]: Now in main()
[ INFO] [1654097836.589222745]: Now inside the callback 
[ INFO] [1654097836.589280267]: The goal value = 1
[ INFO] [1654097836.589942915]: Now inside the callback 
[ INFO] [1654097836.589995519]: The goal value = 2
rosrun model_pkg sampactclient 
[ INFO] [1654097836.262198470]: waiting for server: 
[ INFO] [1654097836.588953751]: Server connection happened!
[ INFO] [1654097836.589535834]:  Inside the servdone callback: server response is: [SUCCEEDED]
[ INFO] [1654097836.589576512]: the received result output = 1 while the goal_stamp = 1 and the difference = 0
[ INFO] [1654097836.589631643]: We have something!
[ INFO] [1654097836.590154107]:  Inside the servdone callback: server response is: [SUCCEEDED]
[ INFO] [1654097836.590195056]: the received result output = 2 while the goal_stamp = 2 and the difference = 0
[ INFO] [1654097836.590257896]: We have something!
rostopic echo /sample_act/goal 
header: 
  seq: 0
  stamp: 
    secs: 1654098248
    nsecs: 966739184
  frame_id: ''
goal_id: 
  stamp: 
    secs: 1654098248
    nsecs: 966739319
  id: "/sampactclient-1-1654098248.966739319"
goal: 
  input: 1
---
header: 
  seq: 1
  stamp: 
    secs: 1654098248
    nsecs: 967598942
  frame_id: ''
goal_id: 
  stamp: 
    secs: 1654098248
    nsecs: 967599137
  id: "/sampactclient-2-1654098248.967599137"
goal: 
  input: 2
### Failure
running server then halting the client and run the client again
rosrun model_pkg sampactservr
[ INFO] [1654098383.093476851]: The goal value = 2564
[ INFO] [1654098395.065501003]: Now inside the callback 
[ INFO] [1654098395.065556897]: The goal value = 1
[ WARN] [1654098395.065570445]: MISMATCH!
[ INFO] [1654098395.065602708]: goal_count = 2565; goal_stamp = 1
[ WARN] [1654098395.065612873]: Aborting goal ... 
rosrun model_pkg sampactclient 
[ INFO] [1654098394.678674901]: waiting for server: 
[ INFO] [1654098395.064987120]: Server connection happened!
[ INFO] [1654098395.065881650]:  Inside the servdone callback: server response is: [ABORTED]
[ INFO] [1654098395.065910727]: the received result output = 2565 while the goal_stamp = 1 and the difference = 2564
[ INFO] [1654098395.065981413]: We have something!
[ WARN] [1654098400.066123658]: Timeout! This goal took too long: 2
