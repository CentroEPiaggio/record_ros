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

bool Record::trigger_command(std_srvs::Trigger::Request& req, std_srvs::Trigger::Response& res){
    ROS_INFO("Record callback");
    if(b_record){
        ros::shutdown();
        res.success = true;
        res.message = "stopping recorder";
    }else{
        b_record = true;
        res.success = true;
        res.message  = "starting recorder";
    }
    return true;
}
