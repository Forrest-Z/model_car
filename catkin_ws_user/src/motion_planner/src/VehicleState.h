/*

 */
#ifndef VEHICLE_STATE_CLASS_H_
#define VEHICLE_STATE_CLASS_H_
#include <nodelet/nodelet.h>
#include <geometry_msgs/PoseWithCovariance.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <autonomos_obstacle_msgs/Obstacles.h>
#include <autonomos_obstacle_msgs/Obstacle.h>
#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

namespace fub_motion_planner{
  class VehicleState {    //: public nodelet::Nodelet
    public:
        VehicleState();
        ~VehicleState();
        //virtual void onInit();

        void setup(ros::NodeHandle & nh);
        /** Retrieve the vehicle's yaw orientation in the world
         **
         ** @return the vehicle's yaw in the world
         */
        double getVehicleYaw() const;
    protected:
        void odometryCallback(const nav_msgs::OdometryConstPtr & msg);
        void callbackObstacles(const autonomos_obstacle_msgs::ObstaclesConstPtr & msg);

    public:
        // last received pose (from odometry message)
        geometry_msgs::PoseWithCovariance m_ego_state_pose;

        // last received position (from odometry message)
        tf::Point m_vehicle_position;

        // timestamp of last received odometry message
        ros::Time m_last_odom_time_stamp_received;
        //Vehicle Speed
        double m_current_speed_front_axle_center;
        //Obstacle list
        autonomos_obstacle_msgs::ObstaclesConstPtr m_obstacle_msg;


    private:
        ros::Subscriber m_subscribe_odom;
        ros::Subscriber m_subscribe_obstacles;

  };

  class TfListener{
    public:
      tf::TransformListener listener;
  };

} // namespace sample_nodelet_ns

#endif /* */
