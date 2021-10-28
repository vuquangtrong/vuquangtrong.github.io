#!/bin/bash
ip route del default
ip route add default dev ppp0
ping google.com -c 10
