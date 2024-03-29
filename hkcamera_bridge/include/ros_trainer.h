#ifndef __ROS_TRAINER_H__
#define __ROS_TRAINER_H__

#include <vision/trainer.h>
#include <ros/ros.h>
#include <vision_bridge/train.h>

#define TRAIN_SERVER_NAME "trian"

using namespace hirop_vision;

class TrainService{

public:
    TrainService(ros::NodeHandle n);

    /**
     * @brief start     启动检测服务
     * @return  0 成功 -1 失败
     */
    int start();

    /**
     * @brief stop      停止检测服务
     * @return      0 成功 -1 失败
     */
    int stop();

private:
    bool trainCallback(vision_bridge::train::Request &req, vision_bridge::train::Response &res);

private:
    ros::NodeHandle mNodeHandle;

    ros::ServiceServer trainServer;

};

#endif
