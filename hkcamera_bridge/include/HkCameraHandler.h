#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "MvCameraControl.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
class HkCameraHandler{
public:
    HkCameraHandler();
    int start();
    int TrrigerOnce(bool type=false);
    int getImageData(cv::Mat& outImage);
    int close();
private:
    int init();

private:
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    void* Camerahandle;
    cv::Mat tempImg;
    bool g_bExit;
    bool use_color;
};
