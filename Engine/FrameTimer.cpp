#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
    last = high_resolution_clock::now();
}

float FrameTimer::Mark()
{
    const auto old = last;
    last = high_resolution_clock::now();
    const duration<float> frameTime = last - old;
    return frameTime.count();
}
