#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int16.hpp"
#include "vehconarch_interfaces/msg/steering_node_resp.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

class SteeringControlNode : public rclcpp::Node
{
public:
    SteeringControlNode() : Node("steering_control_node")
    {
        SteerAg_curr.data=0;
        ramp_.data=0.2;
        publisher_=this->create_publisher<vehconarch_interfaces::msg::SteeringNodeResp>("SteeringResponse",10);
        subscriber_=this->create_subscription<std_msgs::msg::Float64>("steering_cmd",10,std::bind(&SteeringControlNode::StoreSteerAg,this,_1));
        timer_=this->create_wall_timer((0.2s),std::bind(&SteeringControlNode::rampSteerAg,this));
        RCLCPP_INFO(this->get_logger(),"Steering Control Node Running!!");
    }
private:
    void StoreSteerAg(std_msgs::msg::Float64 SteerAg)
    {
        SteerAg_q.push(SteerAg);
    }
    void rampSteerAg()
    {
        if (SteerAg_q.empty()) {
        return; // Do nothing if there are no commands to process
        }
        SteerAg_nxt=SteerAg_q.front();
        std_msgs::msg::Float64 SteerAg_delta;
        SteerAg_delta.data = SteerAg_nxt.data - SteerAg_curr.data;
        SteerAg_curr.data = SteerAg_curr.data + (ramp_.data*SteerAg_delta.data);
        steeringresp_.steerag_curr = SteerAg_curr.data;
        if(SteerAg_delta.data>0)
        {
            steeringresp_.steer_dir = "Steering Right";
        }
        else
        {
            steeringresp_.steer_dir = "Steering Left";
        }
        if(std::abs(SteerAg_delta.data)<0.1)
        {
            SteerAg_q.pop();
        }
        publisher_->publish(steeringresp_);
    }


std_msgs::msg::Float64 ramp_;
vehconarch_interfaces::msg::SteeringNodeResp steeringresp_;
std_msgs::msg::Float64 SteerAg_curr;
std_msgs::msg::Float64 SteerAg_nxt;
std::queue<std_msgs::msg::Float64> SteerAg_q;
rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber_;
rclcpp::Publisher<vehconarch_interfaces::msg::SteeringNodeResp>::SharedPtr publisher_;
rclcpp::TimerBase::SharedPtr timer_;
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SteeringControlNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}