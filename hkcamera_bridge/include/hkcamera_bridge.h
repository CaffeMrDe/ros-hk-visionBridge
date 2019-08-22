#pragma once
#include <ros/ros.h>

#include <hkcamera_bridge/HkCameraData.h>
#include <hkcamera_bridge/getImageData.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <HkCameraHandler.h>

#include <image_transport/image_transport.h>
//using namespace hirop_vision;

#define HKCALL_SERVER_NAME "HkCameraData"
#define HKDATA_CALLBACK  "HkGetImageService"

class HkCameraService{
public:
	HkCameraService(ros::NodeHandle n);
	int stop();
	int start();
	int TrrigerOnce();
private:
	bool  CmdDataCallBack(hkcamera_bridge::HkCameraData::Request &req, \
			hkcamera_bridge::HkCameraData::Response & res);
	bool SendImageData(hkcamera_bridge::getImageData::Request & req,\
			 hkcamera_bridge::getImageData::Response & res);


	int MatToCvBridge(cv::Mat & img, cv_bridge::CvImagePtr &image_ptr);
	ros::ServiceServer TrrgerGrabServer;
	ros::ServiceServer GetImageServer;

	ros::Publisher ImagePub;
	cv::Mat temp;

	HkCameraHandler  *HkHand;
	//节点
	ros::NodeHandle mNodeHandle;
	cv_bridge::CvImagePtr image_ptr;

	bool use_color;

	//image_transport::Publisher image_trainpub;
	//image_transport::ImageTransport it;
};
