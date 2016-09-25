#pragma once

#include <chrono>

class Timer
{
    using milliseconds_t = std::chrono::duration < int, std::milli >;
public:
    Timer();
    void reset();
    // returns number of milliseconds since 
    int get_ticks();

private:
    std::chrono::steady_clock::time_point start{ std::chrono::steady_clock::now() };
    std::chrono::steady_clock::time_point end;
    milliseconds_t duration;
};