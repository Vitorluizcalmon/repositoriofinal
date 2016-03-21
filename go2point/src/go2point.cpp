#include  <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <tf/tf.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Point.h>
#include <math.h>

geometry_msgs::Twist twist;
ros::Publisher twist_pedrodepaula;
    

   // Instantiate quaternion
    geometry_msgs::Quaternion qt;
    geometry_msgs::Point qp;
   

double normalizeAngle(double angle)
{
    if (angle > M_PI)
    {   return (angle - 2*M_PI);
    } else if (angle < -M_PI){
        return (angle + 2*M_PI);
    }   else
        return angle;
}



void calculo(double Xi, double Yi, double ang, double Xf, double Yf)
{
    //Yf = 1.5,    Xf = -3.0;
    std::cout << "Xi:  " << Xi << "  Yi:  " << Yi << std::endl;
     std::cout << "Xf:  " << Xf << "  Yf:  " << Yf << std::endl;
    geometry_msgs::Point Posit;
    double Ot = atan2((Yf-Yi),(Xf-Xi));
    double dif0t = Ot - ang; 
    double difOt = normalizeAngle(dif0t);
    double dist = sqrt(pow((Xf-Xi),2)+pow((Yf-Yi),2));
        
    if (difOt > 0.1 || difOt < -0.1)
          {
            twist.angular.z = 1.01*difOt;
            twist.linear.x = 0.5;
          }
        
    else 
        {   
            
            if (dist < 0.1)
            {
                twist.linear.x = 0;
                twist.angular.z = 0;
            }
            else
            {
                twist.angular.z = 0;
                twist.linear.x = 5;
            }
         }

   
    
    
    twist_pedrodepaula.publish(twist);
            
}

 geometry_msgs::Point LinhaePonto(double Xp, double Yp)
{   
     geometry_msgs::Point p;
    double Delta = 0.6;
    double Xi,Yi,Xf,Yf,Xc,Yc,Beta,Reta1,RetaPW;
    //Pontos iniciais da reta (Xi, Yi);
    //Ponto final da Reta (Xf,Yf);
    // Coordenadas Atuais (Xp,Yp);
    //Ponto que se pretende chegar na reta (Xc,Yc);
     //Atribuindo Valores
    Xi = 4, Yi= 1.5, Xf = -3, Yf = 1.5;
    // Cálculo dos Angulos
    double Ou= atan2((Yp-Yi),(Xp-Xi));
    double Of = atan2((Yf-Yi),(Xf-Xi));
    Beta = Of-Ou;
    // Cálculo das retas
    // Reta do ponto Wi a Wif //   
    Reta1 = sqrt(pow((Xf-Xi),2)+pow((Yf-Yi),2));
    // Reta do ponto P a Wi //      
    RetaPW = sqrt(pow((Xp-Xi),2)+pow((Yp-Yi),2));
    // Reta do ponto inicial ao ponto da reta orgonal entre Reta1 e P // 
    double R = sqrt(pow((RetaPW),2) - pow(RetaPW*sin(Beta),2));    
    // Reta do ponto C  ao ponto ortogonal entre Reta 1 e P //  
   //double RetaCQ = R + Delta;
    //Cálculo de Xc e Yc
    Xc = (R + Delta)*cos(Of) + Xi;
    Yc = (R + Delta)*sin(Of) + Yi;
    

            p.x = Xc;
            p.y = Yc;

    
    return p;
    
}
    
    
void odomCallback(const nav_msgs::OdometryConstPtr &var)
{
    // Copy from received message
    qt = var->pose.pose.orientation;
    qp = var->pose.pose.position;
    // Define double
    double yaw = tf::getYaw(qt);
    // Print to screen result
    
    std::cout << "Yaw: " << yaw;
    std::cout << " Position x : " << qp.x;
    std::cout << " Position y : " << qp.y << std::endl;
    
    geometry_msgs::Point P = LinhaePonto(qp.x,qp.y);  
    calculo(qp.x,qp.y, yaw, P.x, P.y);
    
 
    
}


int main (int argc, char **argv)
{
    
    
    //Start ROS within this node
    ros::init (argc,argv,"go2point");
    // Create Node
    ros::NodeHandle nh;
    // Subscribing to odometry topic
    ros::Subscriber odom_sub = nh.subscribe("/vrep/vehicle/odometry",1,odomCallback);
    // Declare topic to subscribe
    twist_pedrodepaula = nh.advertise <geometry_msgs::Twist>("cmd_vel", 1);
    
    ros::spin();
    
}

// 1ª passo: calcular teta (Ot) pela fórmula Ot = atam2(yf,xf)
// 2ª passo: pegar a diferença de teta e a atual coordenada z --> while (difOt > 0.1) --> difOt = Ot - Zat.
// 3ª passo: if (dist > 0.1) --> v = 1; else v = 0;
