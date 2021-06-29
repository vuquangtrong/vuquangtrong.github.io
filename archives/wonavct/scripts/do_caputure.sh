#!/bin/bash
#Helper script to capture an image with raspifastcamd

pid_file=/tmp/raspifastcamd.pid

if [ ! -e $pid_file ]; then
	echo "Error: The pid file $pid_file does no exist, looks like raspifastcamd is not running."
	exit 1
fi

#for i in $(seq 1 30);
#   do
#        kill -USR1 $(cat $pid_file)
#        sleep 0.2
#    done

#pid=$(cat $pid_file)

#echo "Pid of raspifastcamd was $pid"

#sleep 20

#kill -SIGINT $pid

#echo "Killed raspifastcamd"

#rm $pid_file

#exit 0

while true;
    do
        kill -USR1 $(cat $pid_file)
        sleep 0.3
    done
