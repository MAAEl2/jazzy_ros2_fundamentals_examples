#! /usr/bin/env python3

"""
Description:
    This ROS 2 node periodically publishes "Hello World" messages to a topic.

---------
Publishing Topics:
    The channel containing the "Hello World" message.
    /py_example_topic - std_msgs/String

Subscription Topics:
    None
---------

Author : Mohamed Elwahsh
Date: May 4, 2026   
"""

import rclpy # Import the ROS 2 client library for Python
from rclpy.node import Node # Import the Node class, used for creating nodes

from std_msgs.msg import String # Import String message for ROS 2


class MinimalPyPublisher(Node):
    """Create a MinimalPyPublisher Node

    """
    def __init__(self):
        """create a custom node class for publishing messages

        """
        #initialize the node with a name
        super().__init__('minimal_py_publisher')

        # create a publisher on the topic with a queue size of 10 msgs
        self.publisher_1 = self.create_publisher(String, '/py_example_topic', 10)

        # create a trigger timer of 0.5 seconds
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0


    def timer_callback(self):
        """Callback function executed periodically by the timer
        """
        #create a new String message object
        msg = String()

        #set the message data with  a counter
        msg.data = 'Hello world: %d' % self.i

        # publish the msg to a topic
        self.publisher_1.publish(msg)

        #log a message indicating the message has been published
        self.get_logger().info('Publishing: "%s"' % msg.data)

        self.i = self.i + 1

def main(args=None):
    """Main function to start ROS 2 node
    
    """
    rclpy.init(args=args)

    #create an instance of the minimal publisher node

    minimal_py_publisher = MinimalPyPublisher()

    rclpy.spin(minimal_py_publisher)

    #destroy the node explicitly
    minimal_py_publisher.destroy_node()

    #shutdown ROS 2 communication
    rclpy.shutdown()

if __name__ == '__main__':
    #Execute the main function if the script is run directly
    main()