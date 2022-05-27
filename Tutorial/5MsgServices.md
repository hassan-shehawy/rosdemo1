# CUSTOM MESSAGE
Note: There exists some primitive data types that we use to build a custom message
1. Define the message structure in a .msg file in a "msg" directory
2. Edit the CMake and package.xml files
3. Compile using catkin_make you get a header file in devel/include directory
4. Make a publisher node that can publish this customized message type


# SERVICES
Communication happens in 3 ways:
1. Publisher/Subscriber
2. Client/Service (blocked) 
3. ActionClient/ActionServer
