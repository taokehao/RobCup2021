option(LookAround1, (float)(-0.8f)rightPan, (float)(0.8f)leftPan, (float)(0.34f)tilt, (float)(pi)speed, (HeadMotionRequest::CameraControlMode)(HeadMotionRequest::autoCamera)camera)
{
    /** Set the head motion request. */
    initial_state(setRequest)
    {
        transition
        {
            if (/*action_done && */ state_time > 2000)
                goto target1Reached;
        }
        action
        {
            SetHeadPanTilt(0.f, tilt, 50_deg);
            //  OUTPUT_TEXT(state_time);
        }
    }

    /** This state "notifies" the caller that the requested head angles are reached */
    state(target1Reached)
    {
        transition
        {
            if (state_time > 1000)
                goto target2Reached;
        }
        action
        {
            SetHeadPanTilt(leftPan, tilt, 50_deg); //zuo
                                                   //  OUTPUT_TEXT(state_time);
        }
    }

    state(target2Reached)
    {
        transition
        {
            if (state_time > 2000)
                goto setRequest;
        }
        action
        {
            SetHeadPanTilt(rightPan, tilt, 50_deg); //you
                                                    //  OUTPUT_TEXT(state_time);
        }
    }
}