#include "PCGenNode.h"

using namespace pcl;

PCGenNode::PCGenNode()
: cloudSub(nh.subscribe("/points2", 1, &PCGenNode::cloudCallback, this))
, captureService(nh.advertiseService("capture_cloud", &PCGenNode::captureCloud, this))
, mostRecentCloud(new pcl::PointCloud<pcl::PointXYZ>)
{
    
    cloudProcessed = false;

    
}

//Receive most recent cloud and convert it to PCL message (this is apparently slow, perhaps we can do another way)
void PCGenNode::cloudCallback(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
    pcl::fromROSMsg (*cloud_msg, *mostRecentCloud);
}

//This function is no longer necessary. but i am commenting without being able to test the code so i'm afraid to make changes
void PCGenNode::listenTransform()
{
    ROS_INFO("collecting stuff");
    tf::StampedTransform base2gripper;
    try
    {
        listener.lookupTransform("panda_link7", "panda_link0", ros::Time(0), base2gripper);
        ROS_INFO_STREAM(" base2gripper: " << base2gripper.getOrigin().x() << ", " << base2gripper.getOrigin().y() << ", " <<base2gripper.getOrigin().z() << ", "
                                              << base2gripper.getRotation().x() << ", " << base2gripper.getRotation().y() << ", " << base2gripper.getRotation().z());
        mostRecentTransform = base2gripper;
    }
    catch (tf::TransformException ex)
    {
        ROS_ERROR("%s", ex.what());
        ros::Duration(1.0).sleep();
    }
}

/*When false is received: 
filter point cloud to remove NaN values
add filtered cloud to list
convert tf::StampedTransform to a 4x4 Eigen Matrix4f
add transform to list

when true:
process point clouds
*/
bool PCGenNode::captureCloud(messages::ImageCapture::Request& req, messages::ImageCapture::Response& res)
{
    if (req.x == false)
    {
        ROS_INFO("capturing point cloud [%ld]", (int) cloudList.size());
        //FILTERING STAGE (PRE PROCESSING)
        //pcl::PointCloud<pcl::PointXYZ>::Ptr filteredCloud(new PointCloud<pcl::PointXYZ>);
        pcl::PointCloud<pcl::PointXYZ>::Ptr filter_NaN(new PointCloud<pcl::PointXYZ>);

        std::vector< int > indices;
        //here we can use most recent cloud as output probably, to avoid creating a new variable
        pcl::removeNaNFromPointCloud(*mostRecentCloud, *filter_NaN, indices);

        //Outler removal (lonely points that are spread here and there in the cloud, like annoying mosquitoes
        //There are pthe product of sensors inaccuracy (noise) which registers measrements where there should be any.
        //Filter object (RadiusBased)
        pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_outler(new pcl::PointCloud<pcl::PointXYZ>);
        RadiusOutlierRemoval<pcl::PointXYZ> filter_outler;
        filter_outler.setInputCloud(filter_NaN);
        //Every point must have 10 neighbors within 15cm, or it will be removed
        filter_outler.setRadiusSearch(0.15);
        filter_outler.setMinNeighborsInRadius(10);
        filter_outler.filter(*filtered_outler);

        //Resampling -Downsampling
        pcl::PointCloud<pcl::PointXYZ>::Ptr filteredCloud(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::VoxelGrid<pcl::PointXYZ> filter_voxel;
        filter_voxel.setInputCloud(filtered_outler);
        // We set the size of every voxel to be 1x1x1cm
        // (only one point per every cubic centimeter will survive).
        filter_voxel.setLeafSize(0.01f,0.01f,0.01f);
        filter_voxel.filter(*filteredCloud);


        //pcViewer(filteredCloud);

        //Normal_Estimation(filteredCloud,normals);
        cloudList.push_back(filteredCloud);
        ROS_INFO("After pcViewer function");
        
        tf::StampedTransform base2gripper;
        listener.lookupTransform("panda_link7", "panda_link0", ros::Time(0), base2gripper);
        mostRecentTransform = base2gripper;
        

        
        Eigen::Matrix4f convertedTransform;
        formatTransform(mostRecentTransform, convertedTransform);
        cloudTransforms.push_back(convertedTransform);
        
    }
    else if (req.x == true && cloudProcessed == false)
    {
        ROS_INFO("stitching point clouds...");
        stitchClouds();
        registerModel();

    }

    res.y = true;

}

//Loop through all point clouds, and find correspondences between them. Output should be the 'Full' point cloud merged from all of the views.
void PCGenNode::stitchClouds()
{
    //visualize cloud?
    pcl::PointCloud<pcl::PointXYZ>::Ptr source(new PointCloud<pcl::PointXYZ>), target(new PointCloud<pcl::PointXYZ>);
    ROS_INFO("here");

    //first target is the first point in the cloud. Transform to base frame
    pcl::transformPointCloud(*cloudList[0], *target, cloudTransforms[0]);

    ROS_INFO("here 2");

    for (int i = 0; i < cloudList.size(); i++)
    {
        Eigen::Matrix4f pairTransform;
        pcl::transformPointCloud(*cloudList[i], *source, cloudTransforms[i]);
        pcl::PointCloud<pcl::PointXYZ>::Ptr temp (new PointCloud<pcl::PointXYZ>);
        ROS_INFO("here3");
        pairAlign(source,target,temp, pairTransform);

        target = temp;

    }

    scanResults = target;

}

//To do. Convert Stl model to a point cloud, then use the ICP method to find transformation. finally find the target in base coords.
void PCGenNode::registerModel()
{
    return;
}

//Take two point clouds, and find the transformation between them. Output is the merged point cloud. 
void PCGenNode::pairAlign(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_src, const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_tgt, pcl::PointCloud<pcl::PointXYZ>::Ptr output, Eigen::Matrix4f &final_transform)
{
    pcl::PointCloud<pcl::PointXYZ> cloud_source_registered;
    IterativeClosestPoint<PointXYZ, PointXYZ> icp;

    icp.setInputCloud(cloud_src);
    icp.setInputTarget(cloud_tgt);

     // Set the max correspondence distance to 5cm (e.g., correspondences with higher distances will be ignored)
    icp.setMaxCorrespondenceDistance (0.05);
    // Set the maximum number of iterations (criterion 1)
    icp.setMaximumIterations (50);
    // Set the transformation epsilon (criterion 2)
    icp.setTransformationEpsilon (1e-8);
    // Set the euclidean distance difference epsilon (criterion 3)
    icp.setEuclideanFitnessEpsilon (1);
    // Perform the alignment
    icp.align (cloud_source_registered);

    std::cout << "has converged:" << icp.hasConverged() << " score: " <<
              icp.getFitnessScore() << std::endl;
    std::cout << icp.getFinalTransformation() << std::endl;

    final_transform = icp.getFinalTransformation();

    *output = cloud_source_registered + *cloud_tgt;

}

//Converts a Tf::StampedTransform to an Eigen::Matrix4f
void PCGenNode::formatTransform(tf::StampedTransform tfTransform, Eigen::Matrix4f &eigenTransform)
{
    tf::Matrix3x3 rotTF;
    tf::Vector3 transTF;

    Eigen::Matrix3d R;
    Eigen::Vector3d T;

    rotTF = tfTransform.getBasis();
    transTF = tfTransform.getOrigin();
    ROS_INFO_STREAM(" tfTransform: " << tfTransform.getOrigin().x() << ", " << tfTransform.getOrigin().y() << ", " <<tfTransform.getOrigin().z() << ", "
                                              << tfTransform.getRotation().x() << ", " << tfTransform.getRotation().y() << ", " << tfTransform.getRotation().z());
    tf::matrixTFToEigen(rotTF, R);
    tf::vectorTFToEigen(transTF,T);

    Eigen::Matrix4d Trans;
    Trans.setIdentity();
    Trans.block<3,3>(0,0) = R;
    Trans.block<3,1>(0,3) = T;
    std::cout<<Trans<<std::endl;

    eigenTransform = Trans.cast<float> ();
    ROS_INFO("i've been here");

}

//Cloud viewer gives a library error when used. Perhaps try the pcl::Visualizer or w/e?
void PCGenNode::pcViewer(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_src)
{
    //pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");


    //pcl::PointCloud<pcl::PointXYZRGB>::Ptr ptrCloud(&cloud_src);


    //viewer.showCloud (cloud_src);



}


void PCGenNode::Normal_Estimation(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PointCloud<pcl::Normal>::Ptr& normals)
{
    ROS_INFO("I am in Normal Estimation Function");
    pcl::IntegralImageNormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimation;
    normalEstimation.setInputCloud(cloud);
    // Other estimation methods: COVARIANCE_MATRIX, AVERAGE_DEPTH_CHANGE, SIMPLE_3D_GRADIENT
    // They determine the smoothness of the result, and the running time
    normalEstimation.setNormalEstimationMethod(normalEstimation.AVERAGE_3D_GRADIENT);
    //Depth threshold for computing object borders based on depth changes, in meters.
    normalEstimation.setMaxDepthChangeFactor(0.02f);
    //Factor that influences the size of the area used to smooth the normals.
    normalEstimation.setNormalSmoothingSize(10.0f);
    //Calculatethe normals.
    normalEstimation.compute(*normals);

    /*
    ROS_INFO("Trying to plot ");
    // IN CASE iF WANTED TO VISUALIZE THEM (DOES NOT WORK? )
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer("Normals"));
    viewer->addPointCloud<pcl::PointXYZ>(cloud, "cloud");
    viewer->addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(cloud,normals,20,0.03, "normals");

    while(!viewer->wasStopped())
    {
        ROS_INFO("Plotting...");
        viewer->spinOnce(100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100000));
    }
     */

}