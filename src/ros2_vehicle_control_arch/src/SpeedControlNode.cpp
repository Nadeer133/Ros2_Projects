#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int16.hpp"
#include "vehconarch_interfaces/msg/speed_node_resp.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class SpeedControlNode : public rclcpp::Node
{
public:
    SpeedControlNode() : Node("Speed_Control_Node")
    {
        VehSpd_curr.data=0;
        ramp_.data=0.8;
        publisher_=this->create_publisher<vehconarch_interfaces::msg::SpeedNodeResp>("SpeedResponse",10);
        subscriber_=this->create_subscription<std_msgs::msg::Int16>("vehspd_cmd",10,std::bind(&SpeedControlNode::StoreVehSpd,this,_1));
        timer_=this->create_wall_timer((0.2s),std::bind(&SpeedControlNode::rampVehspd,this));
        RCLCPP_INFO(this->get_logger(),"Speed Control Node Running!!");
    }
private:
    void StoreVehSpd(std_msgs::msg::Int16 VehSpd)
    {
        VehSpd_q.push(VehSpd);
    }
    void rampVehspd()
    {
        if (VehSpd_q.empty()) {
        return; // Do nothing if there are no commands to process
        }
        VehSpd_nxt.data = static_cast<double>(VehSpd_q.front().data);
        if(VehSpd_nxt.data > VehSpd_curr.data)
        {
            vehspdresp_.speed_dir = "Speeding Up";
        }
        else
        {
            vehspdresp_.speed_dir = "Slowing Down";
        }

        std_msgs::msg::Float64 VehSpd_delta;
        VehSpd_delta.data = VehSpd_nxt.data - VehSpd_curr.data;
        VehSpd_curr.data = VehSpd_curr.data + (ramp_.data*VehSpd_delta.data);
        vehspdresp_.speed_curr = VehSpd_curr.data;

        if(/*std::abs(VehSpd_delta.data)<0.8  || */std::abs(VehSpd_curr.data-VehSpd_nxt.data)<0.8)
        {
            VehSpd_q.pop();
            vehspdresp_.speed_curr = VehSpd_nxt.data;
        }
        publisher_->publish(vehspdresp_);
    }


std_msgs::msg::Float64 ramp_;
vehconarch_interfaces::msg::SpeedNodeResp vehspdresp_;
std_msgs::msg::Float64 VehSpd_curr;
std_msgs::msg::Float64 VehSpd_nxt;
std::queue<std_msgs::msg::Int16> VehSpd_q;
rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr subscriber_;
rclcpp::Publisher<vehconarch_interfaces::msg::SpeedNodeResp>::SharedPtr publisher_;
rclcpp::TimerBase::SharedPtr timer_;
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SpeedControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}