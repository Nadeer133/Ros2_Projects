#include "rclcpp/rclcpp.hpp"

class DriverNode : public rclcpp::Node
{
public:
    DriverNode() : Node("Driver_Node")
    {

    }
private:
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DriverNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}