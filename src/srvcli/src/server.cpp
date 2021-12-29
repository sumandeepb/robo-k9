#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class MinimalServer : public rclcpp::Node
{
public:
    MinimalServer() : Node("add_three_ints_server")
    {
        service_ = this->create_service<tutorial_interfaces::srv::AddThreeInts>("add_three_ints", std::bind(&MinimalServer::add, this, _1, _2));
        RCLCPP_INFO(this->get_logger(), "Ready to add three ints.");
    }

private:
    void add(const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,
             std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response> response)
    {
        response->sum = request->a + request->b + request->c;
        RCLCPP_INFO(this->get_logger(), "Incoming request\na: %ld b: %ld c: %ld", request->a, request->b, request->c);
        RCLCPP_INFO(this->get_logger(), "sending back response: [%ld]", (long int)response->sum);
    }

    rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MinimalServer>());
    rclcpp::shutdown();

    return 0;
}
