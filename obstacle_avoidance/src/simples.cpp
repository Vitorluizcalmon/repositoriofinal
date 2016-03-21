#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>



geometry_msgs::Twist twist;

ros::Publisher twist_pub;

// Sonar Subscriber!!!!
void sonarCallback( const std_msgs::Float32ConstPtr &var)
{

    
    if (var->data > 0)
    {
        
        twist.linear.x = 0; //  m/s
        twist.angular.z =  - 1;//   m/s
    }
    else
    {
        twist.linear.x = 1; //  m/s
        twist.angular.z = 0;//   m/s
    
    }
    twist_pub.publish(twist);
        
        
    std::cout << "Recebi  " << var->data << std::endl;
}
int main(int argc, char **argv)
{
    
    ros::init(argc, argv, "simple_avoidance");
    // Start Node
    ros::NodeHandle nh;
    //
    twist_pub = nh.advertise <geometry_msgs::Twist> ("/cmd_vel", 1);
    // Declare topic to subscribe
    ros:: Subscriber sonar_sub = nh.subscribe("/vrep/vehicle/frontSonar", 1, sonarCallback);
    

    
    ros::spin();
    // Declare topic to be published
  //  ros::Publisher twist_pub = nh.advertise <geometry_msgs::Twist> ("obstacle/twist", 1);
}

