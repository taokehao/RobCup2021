option(FollowTheTarget, (float)(0.f) pan)
{
  /** Simply sets the necessary angles */
  initial_state(lookForward)
  {
    action
    { 
      SetHeadPanTilt(pan, 0.38f, 160_deg);
    }
  }
}