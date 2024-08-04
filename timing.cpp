#include "timing.h"
#include <cmath>
#include <iostream>

void Loop_Timing(bool show_timing)
{
    static auto loopStartTime = std::chrono::steady_clock::now();
    static auto loopEndTime = std::chrono::steady_clock::now();
    static auto loopStartTime2 = std::chrono::steady_clock::now();
    static auto loopEndTime2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = loopEndTime - loopStartTime;
    std::chrono::duration<double> elapsed_seconds2 = loopEndTime - loopStartTime;

    loopEndTime2 = std::chrono::steady_clock::now();
    elapsed_seconds2 = loopEndTime2 - loopStartTime2;

    loopEndTime = std::chrono::steady_clock::now();
    elapsed_seconds = loopEndTime - loopStartTime;
    while (elapsed_seconds.count() < .0166666)
    {
        loopEndTime = std::chrono::steady_clock::now();
        elapsed_seconds = loopEndTime - loopStartTime;
    }
    loopStartTime = std::chrono::steady_clock::now();

    if (show_timing)
    {
        std::cout << "Loop duration: " << elapsed_seconds2.count() << "  " << elapsed_seconds.count() << "s\n";
    }
    loopStartTime2 = std::chrono::steady_clock::now();
}
