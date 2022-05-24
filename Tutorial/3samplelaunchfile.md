# SAMPLE LAUNCH FILE
To create a launch file, we usually have a directory called launch, inside it we have the launch files.
A launch file to run both the publisher and subscriber can be something like:
<launch>
	<node name="numpub" pkg= "model_pkg" type= "samplenode" />
	<node name="numsubscale" pkg= "model_pkg" type= "samplesub" />
</launch>