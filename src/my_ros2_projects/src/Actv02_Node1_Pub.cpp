#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
using namespace std::chrono_literals;

class Num_Pub : public rclcpp::Node
{
public:
    Num_Pub() : Node("number_publisher")
    {
        msg.data = 10;
        publisher_= this->create_publisher<example_interfaces::msg::Int64>("number", 10);
        timer_=this->create_wall_timer((3s), std::bind(&Num_Pub::publishnumber, this));
        RCLCPP_INFO(this->get_logger(),"Publisher 'number' has started publishing");
    }
private:
    void publishnumber()
    {
        publisher_->publish(msg);
    }
example_interfaces::msg::Int64 msg;
rclcpp::TimerBase::SharedPtr timer_; 
rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Num_Pub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}