#ifndef ONE_SHOT_KILLABLE_TIMER_CALLBACK_TYPE
#define ONE_SHOT_KILLABLE_TIMER_CALLBACK_TYPE

#include <functional>

typedef std::function<void(void)> TimeoutCallbackType;
typedef std::function<void(void)> KillTimerCallbackType;

#endif  // ONE_SHOT_KILLABLE_TIMER_CALLBACK_TYPE
