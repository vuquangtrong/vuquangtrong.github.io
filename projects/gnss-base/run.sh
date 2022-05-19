#!/bin/bash

# converter
function ddmm2dec() {
    d=$(bc <<< "$1/100")
    m=$(bc <<< "$1-$d*100")
    m=$(bc <<< "scale=6;$m/60")
    echo $d$m
}

# set up COM port
stty -F /dev/ttyS0 115200

# request base mode
echo "unlog" >> /dev/ttyS0
echo "mode base time 60 1.0 2.0" >> /dev/ttyS0
echo "gngga 1" >> /dev/ttyS0

# check the log
lat=''
lon=''
alt=''

while read -r line < /dev/ttyS0; do
    echo $line
    fix=$(echo $line | awk -F',' '{print $7}')

    # gps position mode is fixed, then exit the loop
    if [[ $fix == '7' ]]; then
        lat=$(echo $line | awk -F',' '{print $3}')
        lat=$(ddmm2dec $lat)

        lon=$(echo $line | awk -F',' '{print $5}')
        lon=$(ddmm2dec $lon)

        alt=$(echo $line | awk -F',' '{print $10}')
        break
    fi
done

echo $lat $lon $alt

# clear output
echo "unlog" >> /dev/ttyS0

# request streamer
# from ttyS0, to localhost:2101 using test account at the test mountpoint
./str2str \
    -in serial://ttyS0:115200 \
    -out ntrips://:test@localhost:2101/test \
    -c gnss.cmd
