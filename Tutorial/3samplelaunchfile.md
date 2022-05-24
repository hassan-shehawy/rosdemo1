# SAMPLE LAUNCH FILE
To create a launch file, we usually have a directory called launch, inside it we have the launch files.
A launch file to run both the publisher and subscriber can be something like:
<launch>
	<node name="numpub" pkg= "model_pkg" type= "samplenode" />
	<node name="numsubscale" pkg= "model_pkg" type= "samplesub" />
</launch>
# NOTES
## No need to run roscore
When running roslaunch, you dont have to run roscore before running the nodes
## Visualize data
You can type: rqt_console to see what is goin on
## Record data
You can use rosbag to record data by typing:
rosbag record topic_name
and playback by:
rosbag play bag_file_name