#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>

    double v=0, w=0;
    double b = 0.35;
    double r = 0.1;
    //Define Messages
    std_msgs::Float64 wl,wr;
    ros::Publisher pub_right;
    ros::Publisher pub_left;

void velocity(const geometry_msgs::TwistConstPtr &velocidade)
{
    v = velocidade->linear.x;
    w = velocidade->angular.z;
    double Vr = v + (b/2)*w;
    double Vl = v - (b/2)*w;
     wr.data = Vr/r;
     wl.data = Vl/r;
            
    pub_right.publish(wr);
    pub_left.publish(wl);
}

int main (int argc, char **argv)
{
    
    
    // Start ROS within this mode
    ros::init(argc, argv, "controller");
    // Declaring node
    ros::NodeHandle node;
    // Declare topic to be published
    pub_right = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorRightSpeed", 1);
    
    pub_left = node.advertise<std_msgs::Float64>("/vrep/vehicle/motorLeftSpeed", 1);
    
        
     ros::Subscriber sonar_sub = node.subscribe("/cmd_vel", 1, velocity);
    
    //Define ROS loop_rate
    ros::Rate loop_rate(60);
    

    
    //ROS LOOP
   
        //ROS routines
    ros::spin();
    //loop_rate.sleep();    
        
    }
