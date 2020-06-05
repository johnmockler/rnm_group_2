#include "camera_calibration_node.h"

CameraCalibrationNode::CameraCalibrationNode()
    : imageSub(n.subscribe("/rgb/image_raw", 1, &CameraCalibrationNode::cameraCallback, this))
    , cameraMatrix(cv::Mat::eye(3,3 CV_64F))
    {
        //put internal code for constructor here. Load parameters maybe?
    }

CameraCalibrationNode::cameraCallback(const sensor_msgs::ImageConstPtr& msg)
{
    //convert image from sensor_msg to open cv data type "cv::Mat"
    cv_bridge::CVImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvShare(msg, enc::BGR8);

    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    //cv_ptr is now compatible with open cv. you can run code here. Create other functions as necessary

}