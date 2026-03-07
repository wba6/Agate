/**
 * @brief Include file for process concurrency information
 */

#ifndef AGATE_PROCESSCONCURRENCY_H
#define AGATE_PROCESSCONCURRENCY_H

#include <thread>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
    #include <bit>
#elif defined(__linux__)
    #include <sched.h>
#endif

namespace Agate {

/**
 * @brief On Windows and Linux, retrieves the amount of threads available
 *        to this process. On MacOS/OSX, retrieves the amount of system
 *        threads available as per `std::thread::hardware_concurrency`
 */
inline unsigned int ProcessConcurrency() {
#ifdef _WIN32

    // Windows: Process affinity mask is a 64-bit bitset where each set bit is an available thread
    DWORD_PTR processAffinityMask, systemAffinityMask;
    if (GetProcessAffinityMask(GetCurrentProcess(), &processAffinityMask, &systemAffinityMask)) {
        return std::popcount(processAffinityMask);
    }

#elif defined(__linux__)

    // Linux: sched_getaffinity provides available thread count
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    if (sched_getaffinity(0, sizeof(cpu_set_t), &cpuset) == 0) {
        return CPU_COUNT(&cpuset);
    }
#endif

    // MacOS does not provide thread availability at the process level
    unsigned int concurrency = std::thread::hardware_concurrency();
    if (concurrency == 0) {
        concurrency = 1;
    }

    return concurrency; 
}

} // namespace Agate

#endif
