option(LookAround3, (float)(-0.523f)rightPan, (float)(0.523f)leftPan, (float)(0.32f)tilt, (float)(pi)speed, (HeadMotionRequest::CameraControlMode)(HeadMotionRequest::autoCamera)camera)
{
    /** Set the head motion request. */
    initial_state(setRequest)
    {
        transition
        {
            if (/*action_done && */ state_time > 4000)
                goto target1Reached;
        }
        action
        {
            SetHeadPanTilt(0.1f, tilt, 100_deg);
            //  OUTPUT_TEXT(state_time);
        }
    }

    /** This state "notifies" the caller that the requested head angles are reached */
    state(target1Reached)
    {
        transition
        {
            if (/*action_done && */ state_time > 2000)
                goto target2Reached;
        }
        action
        {
            SetHeadPanTilt(leftPan, tilt, 100_deg); //zuo
                                                    //  OUTPUT_TEXT(state_time);
        }
    }

    state(target2Reached)
    {
        transition
        {
            if (/*action_done && */ state_time > 4000)
                goto targetReached;
        }
        action
        {
            SetHeadPanTilt(0.1f, tilt, 100_deg);
            //  OUTPUT_TEXT(state_time);
        }
    }

    state(targetReached)
    {
        transition
        {
            if (/*action_done && */ state_time > 2000)
                goto setRequest;
        }
        action
        {
            SetHeadPanTilt(rightPan, tilt, 100_deg); //you
                                                     //  OUTPUT_TEXT(state_time);
        }
    }
}
