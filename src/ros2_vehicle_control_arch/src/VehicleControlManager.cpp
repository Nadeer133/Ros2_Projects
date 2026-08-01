#include "rclcpp/rclcpp.hpp"
#include "vehconarch_interfaces/msg/vehicle_command.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/bool.hpp"

using namespace std::placeholders;
using namespace std::chrono_literals;
class VehicleControlManager : public rclcpp::Node
{
public:
    VehicleControlManager() : Node("vehicle_control_manager")
    {
        getData_f = 0;
        vehcomd_subscriber_=this->create_subscription<vehconarch_interfaces::msg::VehicleCommand>("vehicle_command",10,
                                                        std::bind(&VehicleControlManager::publish_all_vehcomnds,this,_1));
        timer_=this->create_wall_timer((2s),std::bind(&VehicleControlManager::timercallback,this));
        steerag_publisher_=this->create_publisher<std_msgs::msg::Float64>("steering_cmd",10);
        vehspd_publisher_=this->create_publisher<std_msgs::msg::Int16>("vehspd_cmd",10);
        breakf_publisher_=this->create_publisher<std_msgs::msg::Bool>("breakf_cmd",10);
        RCLCPP_INFO(this->get_logger(),"Subscribing to vehicle_command topic");
    }
private:
    void publish_all_vehcomnds(vehconarch_interfaces::msg::VehicleCommand vehcomd_recieved_)
    {
        getData_f=1;
        RCLCPP_INFO(this->get_logger(),"Publishing vehicle command");
        std_msgs::msg::Float64 SteerAg;
        std_msgs::msg::Int16 VehSpd;
        std_msgs::msg::Bool break_f;

        SteerAg.data = vehcomd_recieved_.steerag;
        VehSpd.data = vehcomd_recieved_.vehspd;
        break_f.data = vehcomd_recieved_.break_f;
        steerag_publisher_->publish(SteerAg);
        vehspd_publisher_->publish(VehSpd);
        breakf_publisher_->publish(break_f);
        
    }
    void timercallback()
    {
        if(!getData_f)
        {
            RCLCPP_WARN(this->get_logger(),"No data recieved on Topic. Publisher may not be running!!!");
        }
        else{
            getData_f = 0;
        }
    }
bool getData_f;
rclcpp::TimerBase::SharedPtr timer_;
rclcpp::Subscription<vehconarch_interfaces::msg::VehicleCommand>::SharedPtr vehcomd_subscriber_;
rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr steerag_publisher_;
rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr vehspd_publisher_;
rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr breakf_publisher_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<VehicleControlManager>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}