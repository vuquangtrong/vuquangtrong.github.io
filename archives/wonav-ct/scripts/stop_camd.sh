#!/bin/bash
#Helper script to start RaspiFastCamD
current=$(date +%F-%H-%M-%S)
abc="abc"
folder="/mnt/usb/"$current
sudo mkdir -p $folder

pid_file=/tmp/raspifastcamd.pid

if [ ! -e $pid_file ]; then
	echo "Error: The pid file $pid_file does not exist, looks like raspifastcamd is not running."
	exit 1
fi

pid=$(cat $pid_file)

echo "Pid of raspifastcamd was $pid"

kill -SIGINT $pid

echo "Killed raspifastcamd"
#echo `sudo mv ~/*IMU*.* /mnt/usb/$current`
echo `sudo mv /mnt/usb/*.jpg /mnt/usb/$current`

rm $pid_file

exit 0
