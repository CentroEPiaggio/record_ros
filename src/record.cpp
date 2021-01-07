#include "record_ros/record.h"
#include <ros/ros.h>
#include <boost/thread.hpp>

Record::Record(ros::NodeHandle &nh,rosbag::RecorderOptions const& options):
    rosbag::Recorder(options)
{
    service_srv = nh.advertiseService("cmd",&Record::trigger_command,this);
    b_record    = false;

}

void Record::wait_for_callback(){
    ros::Rate r(100); // 60 hz
    while (!b_record && ros::ok())
    {
        ros::spinOnce();
        r.sleep();
    }
}

bool Record::trigger_command(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res){
    ROS_INFO("Record callback");
    if(b_record){
        ros::shutdown();
    }else{
        b_record = true;
    }
    return true;
}
