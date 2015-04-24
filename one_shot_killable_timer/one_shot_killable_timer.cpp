#include "one_shot_killable_timer.h"

One_shot_killable_timer::One_shot_killable_timer(unsigned int aDelayMs, KillTimerCallbackType aKillTimerCallback, TimeoutCallbackType aTimeoutCallback)
    : mDelayMs(aDelayMs),
    mKillTimerCallback(aKillTimerCallback),
    mTimeoutCallback(aTimeoutCallback),
    mShouldKillTimer(false),
    mThreadPtr(nullptr)
{

}

One_shot_killable_timer::~One_shot_killable_timer()
{
    delete mThreadPtr;
}

void One_shot_killable_timer::ThreadFunc(void)
{
    std::unique_lock<std::mutex> lLocker(mWaitMutex);
    mStopTimerCondition.wait_for(lLocker, std::chrono::milliseconds(mDelayMs), [this](){ return mShouldKillTimer; });

    if (mShouldKillTimer)
    {
        mKillTimerCallback();
    }
    else
    {
        mTimeoutCallback();
    }
}

void One_shot_killable_timer::start()
{
    mThreadPtr = new std::thread(&One_shot_killable_timer::ThreadFunc, this);
    mThreadPtr->detach();
}

void One_shot_killable_timer::kill()
{
    std::unique_lock<std::mutex> lLocker(mWaitMutex);
    mShouldKillTimer = true;
    mStopTimerCondition.notify_one();
}
