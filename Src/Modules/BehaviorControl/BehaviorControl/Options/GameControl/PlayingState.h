option(PlayingState)
{
  initial_state(demo)
  {
    action
    {
		if(theRobotInfo.number == 1)  
			Keeper();
		if(theRobotInfo.number == 2)
			Striker();
		if(theRobotInfo.number == 4)
			Defender();
    }
  }
}
