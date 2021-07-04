option(WalkToGoal, (const Pose2f &)speed)
{
    initial_state(setRequest)
    {
        transition
        {
            if (action_done)
                goto align;
        }
        action
        {
            WalkToTarget(Pose2f(50.f, 50.f, 50.f), speed);
        }
    }
    state(align)
    {
        transition
        {
            if (std::abs(theBallModel.estimate.position.y()) < 100.f && std::abs(theBallModel.estimate.position.x()) < 350.f)
                goto setRequest;
        }
        action
        {
            WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(0.f, theBallModel.estimate.position.x() - 200.f, theBallModel.estimate.position.y()));
        }
    }
}