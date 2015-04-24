#ifndef ONE_SHOT_KILLABLE_TIMER
#define ONE_SHOT_KILLABLE_TIMER

#include <mutex>
#include <thread>
#include <condition_variable>
#include "one_shot_killable_timer_callback_type.h"


class One_shot_killable_timer
{
  public:
      One_shot_killable_timer(unsigned int aDelayMs, KillTimerCallbackType aKillTimerCallback, TimeoutCallbackType aTimeoutCallback);
    ~One_shot_killable_timer();

    void start();
    void kill();

  private:
    void ThreadFunc(void);

    bool mShouldKillTimer;
    std::thread* mThreadPtr;
    std::mutex mWaitMutex;
    std::condition_variable mStopTimerCondition;
    unsigned int mDelayMs;
    TimeoutCallbackType mTimeoutCallback;
    KillTimerCallbackType mKillTimerCallback;
};

#endif  // ONE_SHOT_KILLABLE_TIMER
