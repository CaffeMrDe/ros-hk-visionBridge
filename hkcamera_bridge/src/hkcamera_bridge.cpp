#include <hkcamera_bridge.h>
//#include <hkcamera_bridge/Image_data>
//#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>

using namespace ros;

HkCameraService::HkCameraService(ros::NodeHandle n):use_color(false){
 mNodeHandle = n;
 HkHand = new HkCameraHandler();
 //it = image_transport::ImageTransport(mNodeHandle);
}

int HkCameraService::stop(){

}


int HkCameraService::start(){
	
    	mNodeHandle.param("/hkcamera_bridge/use_color", use_color, false);
	
	TrrgerGrabServer = mNodeHandle.advertiseService(HKCALL_SERVER_NAME,\
			&HkCameraService::CmdDataCallBack, this );
	GetImageServer = mNodeHandle.advertiseService(HKDATA_CALLBACK, \
			&HkCameraService::SendImageData, this);

	ImagePub = mNodeHandle.advertise<sensor_msgs::Image>("camera/hk/image_raw", 1);
	//ImagePub = mNodeHandle.advertise<hkcamera_bridge::Image_data>("object_array", 1);
        ROS_INFO("HK service start finish \n");
}

int HkCameraService::TrrigerOnce(){

}


bool HkCameraService::CmdDataCallBack(hkcamera_bridge::HkCameraData::Request &req, \
			hkcamera_bridge::HkCameraData::Response & res){

	int Cmd = req.cmd;
	int ret = -1;
	if(Cmd == 1){
		ret = HkHand->start();
	}else if(Cmd == 2){
		
		ret = HkHand->TrrigerOnce(use_color);

	}else if(Cmd == 3){
		ret = HkHand->getImageData(temp);
		if(0 != ret )
		{
			printf("get data error %d \n ",ret);
			return false;
		}
		//imwrite("/home/de/demo.jpg", temp);
		if(!use_color)
			cvtColor(temp, temp, COLOR_GRAY2RGB);

		MatToCvBridge(temp, image_ptr);
		printf("[ publish, ret %] d\n", ret);	
		ImagePub.publish(image_ptr->toImageMsg());
	}
	else if(Cmd == 4){
		ret = HkHand->close();
	}

	res.result = ret;
	return true;
}

bool HkCameraService::SendImageData(hkcamera_bridge::getImageData::Request & req,\
			 hkcamera_bridge::getImageData::Response & res){
	int Cmd = req.cmd;
	if(Cmd == 1)
	{
		ImagePub.publish(image_ptr->toImageMsg());
	}

}
int HkCameraService::MatToCvBridge(cv::Mat & img, cv_bridge::CvImagePtr &image_ptr){
	image_ptr = boost::make_shared< cv_bridge::CvImage >();
	image_ptr->encoding = sensor_msgs::image_encodings::MONO8;
	//image_ptr = cv_bridge::toCvCopy(msg, "mono8");//rgb8
	image_ptr->image = img;
	return 0;
}


