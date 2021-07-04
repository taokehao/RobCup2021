option(Keeper)
{
    initial_state(start)
  {
    transition
    {
     // if(state_time > 1000)
      //  goto turnToBall;
    }
    action
    {
      HeadControlMode(HeadControl::lookForward);
      Stand();
    }
  }
}