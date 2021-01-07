#ifndef RECORD_ROS_RECORD_H_
#define RECORD_ROS_RECORD_H_

#include "std_srvs/Empty.h"
#include <rosbag/recorder.h>

class Record : public rosbag::Recorder{

public:

    Record(ros::NodeHandle& nh,rosbag::RecorderOptions const& options);

    void wait_for_callback();

private:

    bool trigger_command(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);

private:

    bool                        b_record;
    ros::ServiceServer          service_srv;
    ros::Subscriber             topic_cmd;

};


#endif
