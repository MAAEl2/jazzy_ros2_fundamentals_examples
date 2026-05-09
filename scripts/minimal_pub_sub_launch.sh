#!/bin/bash
# This script launches both the minimal publisher and subscriber nodes for ROS 2.

cleanup() {

    echo "Restarting Ros 2 daemon to cleanup before shutting down any processes"
    ros2 daemon stop
    sleep 1
    ros2 daemon start
    echo "Terminating all ROS 2-related processes..."
    kill 0
    exit
}

trap 'cleanup' SIGINT

# launch the publisher node
ros2 run ros2_fundamentals_examples py_minimal_publisher.py &

sleep 2

# launch the subscriber node
ros2 run ros2_fundamentals_examples py_minimal_subscriber.py

