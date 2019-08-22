#include <ros/ros.h>
//#include "ros_detctor.h"
//#include "ros_trainer.h"
#include "hkcamera_bridge.h"
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "hkcamera_bridge"); 
    ros::NodeHandle n;
    
    HkCameraService hk(n);
    hk.start();

//    DetectorService s(n);
//    TrainService t(n);
//
//    s.start();
//    t.start();

    ros::spin();
    return 0;
}
