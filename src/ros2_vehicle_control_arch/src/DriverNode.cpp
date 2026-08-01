#include "rclcpp/rclcpp.hpp"
#include "vehconarch_interfaces/msg/vehicle_command.hpp"
#include <random>

using namespace std::chrono_literals;

class DriverNode : public rclcpp::Node
{
public:
    DriverNode() : Node("Driver_Node") , counter_(0)
    {
        publisher_=this->create_publisher<vehconarch_interfaces::msg::VehicleCommand>("vehicle_command",10);
        timer_=this->create_wall_timer(1s,std::bind(&DriverNode::publish_VehCommand,this));
        RCLCPP_INFO(this->get_logger(),"Driver Node ready to publish VehCommands");
    }
private:
    void publish_VehCommand()
    {
        RCLCPP_INFO(this->get_logger(),"Publishing!!!");
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis_vehspd(1,200);
        std::uniform_int_distribution<> dis_steerag(-360,360);
        vehcomd_.steerag=dis_steerag(gen);
        vehcomd_.vehspd=dis_vehspd(gen);
        vehcomd_.break_f = 0;
        publisher_->publish(vehcomd_);
    }
int counter_;
vehconarch_interfaces::msg::VehicleCommand vehcomd_;
rclcpp::Publisher<vehconarch_interfaces::msg::VehicleCommand>::SharedPtr publisher_;
rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DriverNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}