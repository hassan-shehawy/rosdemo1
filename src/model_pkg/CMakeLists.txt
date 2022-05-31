cmake_minimum_required(VERSION 3.0.2)
project(model_pkg)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  	     roscpp
  	     rospy
  	     std_msgs
  	     message_generation)

################################################
## Declare ROS messages, services and actions ##
################################################
add_message_files(FILES
		  samsg.msg)

add_service_files(FILES
		  samserv.srv)

generate_messages(DEPENDENCIES
		  std_msgs)

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
