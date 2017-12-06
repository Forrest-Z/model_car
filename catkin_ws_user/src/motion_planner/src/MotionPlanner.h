/*
 * sample_nodelet_class.h
 *
 *  Created on: 2016/09/18
 *      Author: cryborg21
 */
#ifndef MOTION_PLANNER_H_
#define MOTION_PLANNER_H_
#include <nodelet/nodelet.h>
#include "VehicleState.h"

namespace fub_motion_planner{
  class MotionPlanner : public nodelet::Nodelet{
    public:
        MotionPlanner();
        ~MotionPlanner();
        virtual void onInit();
    protected:
      VehicleState m_vehicle_state;
      /** The callback for the timer that triggers the update.
      */
      void callbackTimer(const ros::TimerEvent&);
      // timer triggering our execution // TODO: use WallTimer?
      ros::Timer m_timer;
  };
} // namespace sample_nodelet_ns

#endif /* SAMPLE_NODELET_CLASS_SRC_SAMPLE_NODELET_CLASS_H_ */