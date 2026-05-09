#! /usr/bin/env python3

"""
Description:
    This ROS 2 node subscribe to "Hello World" messages.

--------
Publishing Topics:
    None

Subscription Topics:
    The channel containing the "Hello World" message.
    /py_example_topic - std_msgs/String

--------
Author : Mohamed Elwahsh
Date: May 4, 2026   

"""

import rclpy # Import the ROS 2 client library for Python
from rclpy.node import Node # Import the Node class, used for creating nodes

from std_msgs.msg import String # Import String message for ROS 2

class MinimalPySubscriber(Node):
    def __init__(self):
        super().__init__('minimal_py_subscriber')

        self.subscriber_1 = self.create_subscription(
                                                    String, 
                                                    '/py_example_topic', 
                                                    self.listener_callback, 
                                                    10
                                                    )


    def listener_callback(self, msg):
        self.get_logger().info(f'I heard: "{msg.data}"')
    
def main(args=None):
    rclpy.init(args=args)

    minimal_py_subscriber = MinimalPySubscriber()

    rclpy.spin(minimal_py_subscriber)

    minimal_py_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()