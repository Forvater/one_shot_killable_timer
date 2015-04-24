#include <iostream>
#include "one_shot_killable_timer.h"

void timeout_callback()
{
    std::cout << "Timeout!" << std::endl;
}

void kill_timer_callback()
{
    std::cout << "Timer killed!" << std::endl;
}

int main()
{
    unsigned int lDelay = 0;

    std::cout << "Enter delay in milliseconds: " << std::endl;
    std::cin >> lDelay;

    One_shot_killable_timer lTimer(lDelay, kill_timer_callback, timeout_callback);
    lTimer.start();
    std::cout << "Timer started with " << lDelay << " milliseconds delay" << std::endl;
    std::cout << "Enter 1 to kill timer, enter 2 to exit" << std::endl;

    int lChoice = 0;
    bool lShouldExit = false;
    while (!lShouldExit)
    {
        std::cin >> lChoice;
        if (lChoice == 1)
        {
            lTimer.kill();
        }
        else if (lChoice == 2)
        {
            lShouldExit = true;
        }
    }
}
