/** behavior for the ready state */
option(ReadyState,(int)(0)number)
{
  /* position has been reached -> stand and wait */
	static Vector2f Goal=Vector2f(0,0);
	static Vector2f Goal1=Vector2f(-900,0);
	common_transition{
        if(number==1){
			Goal1=Vector2f(-4000,0);
		}
		if(number==2){
			Goal1=Vector2f(-900,0);
		}
		if(number==4){
			Goal1=Vector2f(-2000,0);
		}
		if(std::abs(Transformation::fieldToRobot(theRobotPose,Goal1).norm()) < 50)
			goto stand;
		else if(std::abs(Transformation::fieldToRobot(theRobotPose,Goal1).norm()) > 1000  &&  std::abs(Transformation::fieldToRobot(theRobotPose,Goal1).angle()) > 25_deg )
			goto Turn;
		else
			goto walk;
	}

	initial_state(stand)
	{
		action
		{
		    HeadControlMode(HeadControl::lookForward);
			if(std::abs(Transformation::fieldToRobot(theRobotPose,Goal).angle()) > 15_deg)
				WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(Transformation::fieldToRobot(theRobotPose,Goal).angle(), 0.f, 0.f));
		    else
				Stand();
		}
	}
	  
	state(Turn)
	  {
		action
		{
		    HeadControlMode(HeadControl::lookForward);
		    WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(Transformation::fieldToRobot(theRobotPose,Goal1).angle(), 0.f, 0.f));
		}
	}
	  
	state(walk)
	  {
		action
		{
		    HeadControlMode(HeadControl::lookForward);
		    if(theLibCodeRelease.Obstacle_Front||theLibCodeRelease.Obstacle_Arm)
				theMotionRequest=thePathPlanner.plan(Pose2f(0,Goal1),Pose2f(0.85f,0.85f,0.85f),false); 
		    else if(std::abs(Transformation::fieldToRobot(theRobotPose,Goal1).norm()) < 500)
				WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(Transformation::fieldToRobot(theRobotPose,Goal).angle(), Transformation::fieldToRobot(theRobotPose,Goal1)));
			else
				WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(Transformation::fieldToRobot(theRobotPose,Goal1).angle(), Transformation::fieldToRobot(theRobotPose,Goal1)));
		}
	}
  
}
