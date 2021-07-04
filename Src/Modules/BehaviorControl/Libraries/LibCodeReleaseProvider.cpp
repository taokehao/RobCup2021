/**
 * @file LibCodeReleaseProvider.cpp
 */

#include "LibCodeReleaseProvider.h"
#include "Tools/Math/Transformation.h"
//#include "Tools/Math/Eigen.h"
#include "Representations/Communication/TeamData.h"
#include "Tools/Debugging/DebugDrawings.h"
MAKE_MODULE(LibCodeReleaseProvider, behaviorControl);

void LibCodeReleaseProvider::update(LibCodeRelease& libCodeRelease)
{
  libCodeRelease.timeSinceBallWasSeen = theFrameInfo.getTimeSince(theBallModel.timeWhenLastSeen);
  libCodeRelease.angleToGoal = (theRobotPose.inversePose * Vector2f(4500.f, 0.f)).angle();//theFieldDimensions.xPosOpponentGroundline
  libCodeRelease.between = [&](float value, float min, float max) -> bool
  {
    return value >= min && value <= max;
  };
  libCodeRelease.angleToOwnGoal = (theRobotPose.inversePose * Vector2f(theFieldDimensions.xPosOwnGroundline, 0.f)).angle();

  libCodeRelease.globalballx = (float) theRobotPose.translation.x() + (float)std::sqrt(std::pow(theBallModel.estimate.position.x() ,2) + std::pow(theBallModel.estimate.position.y(),2))* std::cos(theRobotPose.rotation + theBallModel.estimate.position.angle());//球的全局坐标x
  
  libCodeRelease.globalbally = (float) theRobotPose.translation.y() + (float)std::sqrt(std::pow(theBallModel.estimate.position.x() ,2) + std::pow(theBallModel.estimate.position.y(),2))* std::sin(theRobotPose.rotation + theBallModel.estimate.position.angle());//球的全局坐标y
  	static bool judge_flag_front,judge_flag_arm=false;
	static Vector2f temp_pose1,temp_pose2,temp_pose3,temp_pose4;
	judge_flag_arm=false;
	judge_flag_front=false;
    for(const auto& obstacle : theObstacleModel.obstacles){
		temp_pose2.x()=theRobotPose.translation.x()-libCodeRelease.Ball_GlobalPoseEs.x();
		temp_pose2.y()=theRobotPose.translation.y()-libCodeRelease.Ball_GlobalPoseEs.y();
		temp_pose1=Transformation::robotToField(theRobotPose,obstacle.center);
		temp_pose1.x()=temp_pose1.x()-libCodeRelease.Ball_GlobalPoseEs.x();
		temp_pose1.y()=temp_pose1.y()-libCodeRelease.Ball_GlobalPoseEs.y();
		if(obstacle.center.norm()<400||(obstacle.center.norm()<600&&std::abs(obstacle.center.angle())<60_deg))
			judge_flag_front=true;
		if(obstacle.center.norm()<600)
			judge_flag_arm=true; 
	}
    if(judge_flag_front)
        libCodeRelease.Obstacle_Front=true;
    else
        libCodeRelease.Obstacle_Front=false;
    if(judge_flag_arm)
        libCodeRelease.Obstacle_Arm=true;    
    else
        libCodeRelease.Obstacle_Arm=false;

    /***障碍物检测函数*/
    DECLARE_DEBUG_DRAWING("test", "drawingOnField");
//    CROSS("test", ControlParameter.Pose_Goal.x(),ControlParameter.Pose_Goal.y(), 50, 50, Drawings::solidPen, ColorRGBA::yellow);
//    LINE("test", ControlParameter.Ball_GlobalPoseEs.x(), ControlParameter.Ball_GlobalPoseEs.y(), ControlParameter.Pose_Goal.x(), ControlParameter.Pose_Goal.y(), 40, Drawings::solidPen, ColorRGBA::gray);
}
