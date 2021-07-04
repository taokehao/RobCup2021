/** A test striker option without common decision */
option(Striker)
{
  initial_state(start)
  {
    transition
    {
      if(state_time > 1000)
        goto turnToBall;
    }
    action
    {
      HeadControlMode(HeadControl::lookForward);
      Stand();
    }
  }

  state(turnToBall)
  {
    transition
    {
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto searchForBall;
      if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
        goto walkToBall;
    }
    action
    {
      HeadControlMode(HeadControl::lookForward);

    }
  }

  state(walkToBall)
  {
    transition
    {
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto searchForBall;
      if(theBallModel.estimate.position.norm() < 500.f)
        goto alignToGoal;
    }
    action
    {
      HeadControlMode(HeadControl::lookForward);

    }
  }

  state(alignToGoal)
  {
    transition
    {
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto searchForBall;
      if(std::abs(theLibCodeRelease.angleToGoal) < 10_deg && std::abs(theBallModel.estimate.position.y()) < 100.f)
        goto alignBehindBall;
    }
    action
    {
      HeadControlMode(HeadControl::lookForward);
      WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(theLibCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 400.f, theBallModel.estimate.position.y()));
    }
  }

  state(alignBehindBall)
  {
    transition
    {
      if(theLibCodeRelease.timeSinceBallWasSeen > theBehaviorParameters.ballNotSeenTimeOut)
        goto searchForBall;
      if(theLibCodeRelease.between(theBallModel.estimate.position.y(), 20.f, 50.f)
         && theLibCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 170.f)
         && std::abs(theLibCodeRelease.angleToGoal) < 2_deg)
        goto kick;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(theLibCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() - 30.f));
    }
  }

  state(kick)
  {
    transition
    {
      if(state_time > 3000 || (state_time > 10 && action_done))
        goto start;
    }
    action
    {
      HeadControlMode(HeadControl::lookForward);
      InWalkKick(WalkKickVariant(WalkKicks::forward, Legs::left), Pose2f(theLibCodeRelease.angleToGoal, theBallModel.estimate.position.x() - 160.f, theBallModel.estimate.position.y() - 55.f));
    }
  }

  state(searchForBall)
  {
    transition
    {
      if(theLibCodeRelease.timeSinceBallWasSeen < 300)
        goto turnToBall;
    }
    action
    {
      HeadControlMode(HeadControl::lookForward);
      
    }
  }
}
