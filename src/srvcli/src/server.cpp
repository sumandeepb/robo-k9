#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class MinimalServer : public rclcpp::Node
{
public:
    MinimalServer() : Node("add_two_ints_server")
    {
        service_ = this->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", std::bind(&MinimalServer::add, this, _1, _2));
        RCLCPP_INFO(this->get_logger(), "Ready to add two ints.");
    }

private:
    void add(const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
             std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(), "Incoming request\na: %ld b: %ld", request->a, request->b);
        RCLCPP_INFO(this->get_logger(), "sending back response: [%ld]", (long int)response->sum);
    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalServer>());
    rclcpp::shutdown();

    return 0;
}
