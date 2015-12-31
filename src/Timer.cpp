#include "Timer.h"

#include <chrono>

void Timer::reset()
{
    start = std::chrono::steady_clock::now();
}

int Timer::get_ticks()
{
    end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<milliseconds_t>(end - start);
    return duration.count();
}
