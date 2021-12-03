#include "duration.h"

namespace us_duration
{
    static std::chrono::steady_clock::time_point start;

    void tic()
    {
        start = std::chrono::steady_clock::now();
    }

    long long toc()
    {
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return duration.count();
    }
}