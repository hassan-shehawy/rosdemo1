# ROS PARAMETER SERVER
Very useful tool with useful commands like:
rosparam list
rosparam set
rosparam get
rosparam delete

# NODE TO PULL PARAMTER(S)
ros::init(argc, argv, "pullparam"); 
ros::NodeHandle nh; 
double pp,ii,dd;
if (nh.getParam("/pid_gains/p", pp)) 
ROS_INFO("Proportional gain = %f",pp);

## compiling
add_executable(pullparam src/pullparam.cpp)
target_link_libraries(pullparam ${catkin_LIBRARIES})

## launch file
<launch>
	<rosparam command="load" file="$(find model_pkg)/parms/pidgains.yaml" />
	<node name="pullparam" pkg= "model_pkg" type= "pullparam" />
</launch>

## interactig
roslaunch model_pkg pullparams.launch
rosrun model_pkg pullparam 
[ INFO] [1654099999.325690317]: Proportional gain = 10.800000
[ INFO] [1654099999.326983351]: Derivative gain = 13.500000
[ INFO] [1654099999.327414130]: Integral gain = 11.700000
rosparam delete /pid_gains/
rosrun model_pkg pullparam 
[ WARN] [1654100023.371941303]: p gain value was not found in the parameter server
[ WARN] [1654100023.373272224]: i gain value was not found in the parameter server
[ WARN] [1654100023.373998470]: d gain value was not found in the parameter server

