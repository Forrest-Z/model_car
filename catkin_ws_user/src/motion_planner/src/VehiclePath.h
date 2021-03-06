#ifndef VEHICLE_PATH_CLASS_H_
#define VEHICLE_PATH_CLASS_H_

#include <nodelet/nodelet.h>
#include <nav_msgs/Odometry.h>
#include "math.h"
#include <nav_msgs/Path.h>
#include <ros/ros.h>
#include <tf/tf.h>

namespace fub_motion_planner{
  class FrenetCoordinate{
  public:
    double s; //lenth of the road along the center line
    double d; //lateral distance wrt center of lane/road
    double k; //curvature
    double th; // angle wrt to base frame or base frame angle in frenetpath variable
    FrenetCoordinate(double s, double d, double k, double th){
      this->s = s;
      this->d = d;
      this->k = k;
      this->th = th;
    }
  };
  class VehiclePath{
    public:
      VehiclePath();
      ~VehiclePath();
      void setup(ros::NodeHandle & nh);

      //TODO These functions are working but needs further improvement to make them work better.
      //TODO  It loses track sometimes and conversion is mess with 5-20cms of error which is terrible sometimes
      // Observe each step of xy and frenet transform and fix the issue
      FrenetCoordinate getFenet(tf::Point xy_pt, double theta);
      tf::Point getXY(FrenetCoordinate frenet_pt);
      double distance(tf::Point a, tf::Point b){
        return sqrt((b[0]-a[0])*(b[0]-a[0]) + (b[1]-a[1])*(b[1]-a[1]));
      }
      double slope(tf::Point a, tf::Point b){
        return atan2((b[1]-a[1]),(b[0]-a[0]));
      }
    private:
      void RoutePlannerCallback(const nav_msgs::Path & msg);
      /*returns index of he closest way point to given point*/
      int closestWayPoint(tf::Point pt);
      /*returns index of he next way point to given point*/
      int NextWayPoint(tf::Point pt,double theta);
      double calc_curvature(tf::Point pts0,tf::Point pts1,tf::Point pts2);
      void calc_speed_limit();
      //creates a frenet coordinate frame using the m_path and fills up frenet_path
      void transformToXYandFrenet();
    public:
      //Currently planned path
      nav_msgs::Path m_path;
      bool route_path_exists=false;
      //path in points only
      std::vector<tf::Point> xy_path;
      //Frenet Path
      std::vector<FrenetCoordinate> frenet_path;
      std::vector<double> speed_limit;
    private:
      ros::Subscriber m_subscribe_route_planner;
      ros::Publisher path_with_speed_profiles;
      //TODO this should be part of info read from the rndf file or supplied from the behavioral layer
      const double kLegalSpeedLimit = 1.5;
      const double kMinSpeedLimit = 0.4;//added as errors in curvature calc can drop the limit to too low
      const double kMaxLatAccLimit = 0.3;
  };
}
#endif /*  vehicle path*/
