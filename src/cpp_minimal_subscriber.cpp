/**
 * @file cpp_minimal_subscriber.cpp
 * @author Mohamed Elwahsh
 * @brief A minimal subscriber node in C++ that subscribes to messages on a ROS 2 topic
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 * 
 * ----------
 * Subscription Topics:
 * String message
 * /cpp_example_topic - std_msgs/msg/String 
 * 
 * ----------
 * Publishing Topics:
 * None
 */

#include "rclcpp/rclcpp.hpp" // Include the ROS 2 C++ client library header
#include "std_msgs/msg/string.hpp" // Include the header for the String message type

using std::placeholders::_1; // Placeholder for the callback function

class MinimalCppSubscriber : public rclcpp::Node // Define a class that inherits from rclcpp::Node
{

public:
    MinimalCppSubscriber() : Node("minimal_cpp_subscriber")
    {
        subscriber_ = create_subscription<std_msgs::msg::String>(
            "/cpp_example_topic", 10, // Subscribe to the "/cpp_example_topic" topic with a queue size of 10
            std::bind(&MinimalCppSubscriber::topicCallback, this, _1)); // Bind the topicCallback function to handle incoming messages
    
        RCLCPP_INFO(get_logger(), "Subscriber ready to receive messages"); // Log that the subscriber is ready
    }

    void topicCallback(const std_msgs::msg::String & msg) const // Define the callback function for incoming messages
    {
        RCLCPP_INFO_STREAM(get_logger(), "I heard: " << msg.data.c_str()); // Log the received message
    }
   
private:    
    //member variables
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr 
        subscriber_; // the subscriber object
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); // Initialize the ROS 2 system
    
    auto minimal_cpp_subscriber_node = std::make_shared<MinimalCppSubscriber>(); // Create an instance of the MinimalCppSubscriber class
    rclcpp::spin(minimal_cpp_subscriber_node); // Spin the node to process callbacks
    rclcpp::shutdown(); // Shutdown the ROS 2 system
    return 0; // Return success
}