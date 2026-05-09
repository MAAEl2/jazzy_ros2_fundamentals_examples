/**
 * @file cpp_minimal_publisher.cpp
 * @author Mohamed Elwahsh
 * @brief A minimal publisher node in C++ that publishes a string message at 2Hz.
 * @version 0.1
 * @date 2026-05-04
 * 
 * @copyright Copyright (c) 2026
 */

#include "rclcpp/rclcpp.hpp" // Include the ROS 2 C++ client library header
#include "std_msgs/msg/string.hpp" // Include the header for the String message type

using namespace std::chrono_literals; // Handles time duration

class MinimalCppPublisher : public rclcpp::Node // Define a class that inherits from rclcpp::Node
{

public:
    MinimalCppPublisher() : Node("minimal_cpp_publisher"), count_(0)
    {
        publisher_ = create_publisher<std_msgs::msg::String>(
            "/cpp_example_topic", 10); // Create a publisher for the "/cpp_example_topic" topic with a queue size of 10
        timer_ = create_wall_timer(500ms,
            std::bind(&MinimalCppPublisher::timerCallback, this)); // Create a timer that calls the timerCallback function every 500 milliseconds
    
        RCLCPP_INFO(get_logger(), "Publisher at 2Hz"); // Log that the publisher has started
    }

    void timerCallback()
    {
        auto message = std_msgs::msg::String(); // Create a new String message
        message.data = "Hello, world! " + std::to_string(count_++); // Set the data field of the message to a string with the count
        RCLCPP_INFO(get_logger(), "Publishing: '%s'", message.data.c_str()); // Log the message being published
        publisher_->publish(message); // Publish the message
    }

private:
    size_t count_; // A counter to keep track of how many messages have been published
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr 
        publisher_; // the publisher object
    rclcpp::TimerBase::SharedPtr 
        timer_; // the timer object
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); // Initialize the ROS 2 system
    
    auto minimal_cpp_publisher_node = std::make_shared<MinimalCppPublisher>(); // Create an instance of the MinimalCppPublisher class
    rclcpp::spin(minimal_cpp_publisher_node); // Spin the node to process callbacks
    rclcpp::shutdown(); // Shutdown the ROS 2 system
    return 0; // Return success
}