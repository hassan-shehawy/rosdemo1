cmake_minimum_required(VERSION 3.0.2)
project(model_pkg)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  	     roscpp
  	     rospy
  	     std_msgs
  	     message_generation
	     actionlib_msgs
	     actionlib)

################################################
## Declare ROS messages, services and actions ##
################################################
add_message_files(FILES
		  samsg.msg)

add_service_files(FILES
		  samserv.srv)

add_action_files(FILES
		  samact.action)

generate_messages(DEPENDENCIES
		  std_msgs
		  actionlib_msgs)

###################################
## catkin specific configuration ##
###################################
catkin_package(CATKIN_DEPENDS message_runtime)


###########
## Build ##
###########
include_directories(${catkin_INCLUDE_DIRS} include)

add_executable(samplenode src/samplenode.cpp)
target_link_libraries(samplenode ${catkin_LIBRARIES})

add_executable(samplesub src/samplesub.cpp)
target_link_libraries(samplesub ${catkin_LIBRARIES})

add_executable(samclass src/samclass.cpp)
target_link_libraries(samclass ${catkin_LIBRARIES})

add_executable(samcustmsgpub src/samcustmsgpub.cpp)
target_link_libraries(samcustmsgpub ${catkin_LIBRARIES})

add_executable(samserv src/samserv.cpp)
target_link_libraries(samserv ${catkin_LIBRARIES})

add_executable(samclient src/samclient.cpp)
target_link_libraries(samclient ${catkin_LIBRARIES})

add_executable(sampactservr src/sampactservr.cpp)
target_link_libraries(sampactservr ${catkin_LIBRARIES})

add_executable(sampactclient src/sampactclient.cpp)
target_link_libraries(sampactclient ${catkin_LIBRARIES})

add_executable(pullparam src/pullparam.cpp)
target_link_libraries(pullparam ${catkin_LIBRARIES})
