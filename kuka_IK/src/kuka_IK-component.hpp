/***************************************************************************

    File:           kuka-IK-component.hpp
    Author(s):      Gajamohan Mohanarajah/Francisco Ramos
    Affiliation:    IDSC - ETH Zurich
    e-mail:         gajan@ethz.ch/framosde@ethz.ch
    Start date:	    11th April 2011
    Last update:	11th May 2011

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/

#ifndef OROCOS_KUKA_IK_COMPONENT_HPP
#define OROCOS_KUKA_IK_COMPONENT_HPP

#include <rtt/RTT.hpp>
#include <iostream>

#include <geometry_msgs/Pose.h>
#include <sensor_msgs/JointState.h>
#include "KukaLWR_Kinematics.hpp"

namespace kuka_IK{
class kuka_IK
    : public RTT::TaskContext
{
 public:
    kuka_IK(string const& name);

    bool configureHook();
    bool startHook();
    void updateHook();
    void stopHook();
    void cleanupHook();

 private:

   /** \brief function handle for the input_cartPosPort
		*
		*  \param portInterface
		*/
   bool cartPosInputHandle(RTT::base::PortInterface* portInterface);
   /**
    * @brief intermediate command variables
    */
   std::vector<double> commndedPoseJntPos;
   geometry_msgs::Pose commandedPose;
   std::vector<double> jntPos;
   ///@}

   ///Dimensionality reduction: Grid parameters
   int xI,yI,y_inc;
   ///Dimensionality reduction: logFile
   ofstream logFile;

 protected:
       /// Dataport containing commanded Cartesian pose
       RTT::InputPort< geometry_msgs::Pose > input_cartPosPort;
       /// Dataport containing the command in joint angles
       RTT::OutputPort< sensor_msgs::JointState > output_jntPosPort;
       /// Dataport containing the measured joint angles from the Robot
       RTT::InputPort< std::vector<double> > msr_jntPosPort;
       /// Dataport containing the measured Cartesian position from the Robot
       RTT::InputPort<geometry_msgs::Pose> cartPosPort;
};
}//end of name space
#endif
