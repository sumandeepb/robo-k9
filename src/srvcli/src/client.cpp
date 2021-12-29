#include <chrono>
#include <cstdlib>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"

using namespace std::chrono_literals;

class MinimalClient : public rclcpp::Node
{
public:
    MinimalClient() : Node("add_three_ints_client")
    {
        client_ = this->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");
    }

    int spin_custom(int argc, char **argv)
    {
        if (argc != 4)
        {
            RCLCPP_INFO(this->get_logger(), "usage: add_three_ints_client X Y Z");
            return 1;
        }

        auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
        request->a = atoll(argv[1]);
        request->b = atoll(argv[2]);
        request->c = atoll(argv[3]);

        while (!client_->wait_for_service(1s))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return 0;
            }
            RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
        }

        auto result = client_->async_send_request(request);
        // Wait for the result.
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(this->get_logger(), "Sum: %ld", result.get()->sum);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service add_three_ints");
        }

        return 0;
    }

private:
    rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    MinimalClient client_obj;
    client_obj.spin_custom(argc, argv);

    rclcpp::shutdown();

    return 0;
}
