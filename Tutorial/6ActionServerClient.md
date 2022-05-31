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

## compiling

## interactig

