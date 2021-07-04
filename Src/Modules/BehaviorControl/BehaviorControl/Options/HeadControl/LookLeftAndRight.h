option(LookLeftAndRight, (float) (1.f) rightPan, (float) (-1.f) leftPan, (float) (0.28f) tilt,(float)(pi) speed, (HeadMotionRequest::CameraControlMode)(HeadMotionRequest::autoCamera) camera)
{
  /** Set the head motion request. */
  initial_state(setRequest)
  {
    transition
    {
      if(action_done)
        goto targetReached;
    }
    action
    {
      SetHeadPanTilt(rightPan, tilt, 30_deg);
    }
  }

  /** This state "notifies" the caller that the requested head angles are reached */
  target_state(targetReached)
  {
    transition
    {
	  if(action_done)
      goto setRequest;
    }
    action
    {
      SetHeadPanTilt(leftPan, tilt, 30_deg);
    }
  }
}