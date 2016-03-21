#include <ros/ros.h>
#include <std_msgs/String.h>
#include <iostream>

int main(int argc, char **argv)
{
    /*
    Forma de imprimir na rows:
    ROS_INFO("Hello World using ROS function!");
    return 0;
    */
    
    ros::init( argc , argv ,"ros_pub");
    
    ros::NodeHandle node;
    
    ros::Publisher pub = node.advertise <std_msgs::String>("ros_world",1);
    
    ros::Rate loop_rate(10);
    
    std_msgs::String msg;
    
    while(ros::ok())
    {
        msg.data ="Hello World!";
        
        //std::cout <<"Publishing ... "<<std::endl;
        ROS_INFO("Publishing...");
        pub.publish(msg);
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    
    /*ros::init(argc,argv,"Node A")
        
    ros::NodeHandle node;
    
    ros::Publisher pub = node.advertise < > ("","");

    ros::Rate loop_rate();
    */
    
}