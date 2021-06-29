#!/bin/bash
###	mount usb	###
cm=$(mountpoint /mnt/usb)
cup=$(lsblk | grep "sd[a-z][0-9]")
usb=$(ls /dev/sd[a-z][0-1])
er=""
ur="/mnt/usb is not a mountpoint"
mr="/mnt/usb is a mountpoint"

if [ "$cm" == "$ur" ] && [ "$cup" != "$er" ]; then
	echo `sudo mount -t vfat $usb /mnt/usb -o uid=pi,gid=pi`
	echo "Mounting"
elif [ "$cm" == "$mr" ] && [ "$cup" != "$er" ]; then
	echo "Mounted"
else
exit
fi
echo "mount USB Successful!" 

###	Start Fastcamd	###
pid_file=/tmp/raspifastcamd.pid
if [ -e $pid_file ]; then
	echo "Error: The pid file $pid_file exists, looks like raspifastcamd is already running."
	echo "If this is not the case delete the file."
	exit 1
fi

output_file=${1-/mnt/usb/tmp%05d.jpg}
echo "Output will be written to $output_file"
./raspifastcamd -o $output_file &
pid=$!
echo "Pid of raspifastcamd is $pid"

### register PI ###
echo $pid > $pid_file


### done
exit 0
