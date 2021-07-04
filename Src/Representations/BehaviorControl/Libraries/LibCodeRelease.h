/**
 * @file LibCodeRelease.h
 */

#pragma once
#include "Tools/Function.h"
#include "Tools/Math/Eigen.h"
#include "Tools/Math/Pose2f.h"
//#include "Representations/Perception/PlayersPercepts/PlayersFieldPercept.h"
#include "Tools/Modeling/Obstacle.h"
#include "Representations/Modeling/TeamBallModel.h"
#include "Representations/Communication/TeamData.h"
//#include "Modules/BehaviorControl/BehaviorControl/ParameterDefine.h"

STREAMABLE(LibCodeRelease,
{
	FUNCTION(bool(float value, float min, float max)) between,

	(float) angleToGoal,
	(float) angleToOwnGoal,
	(float) timeSinceBallWasSeen,
	(float) globalballx,
	(float) globalbally,
	(bool)(false) Obstacle_Arm,
	(bool)(false) Obstacle_Front,
	(Vector2f)(Vector2f::Zero())Ball_GlobalPoseEs,  
});
