//
// Created by Mustafa Mert Aladağ on 19.11.2024.
//

#ifndef __UTILS_H__
#define __UTILS_H__

#include <chrono>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define __microseconds(a) std::chrono::duration<double, std::micro>(a).count()
#define __milliseconds(a) std::chrono::duration<double, std::milli>(a).count()
#define __seconds(a) std::chrono::duration<double>(a).count()

#define __timeNow() std::chrono::high_resolution_clock::now()

enum class TimeUnit
{
    MICROSECONDS,
    MILLISECONDS,
    SECONDS
};

template<typename F, typename... Args>
double benchmark(TimeUnit unit, F func, Args &&... args)
{
    TimeVar t1 = __timeNow();
    func(std::forward<Args>(args)...);
    TimeVar t2 = __timeNow();

    switch (unit)
    {
        case TimeUnit::MICROSECONDS:
            return __microseconds(t2 - t1);
        case TimeUnit::MILLISECONDS:
            return __milliseconds(t2 - t1);
        case TimeUnit::SECONDS:
            return __seconds(t2 - t1);
    }

    return __microseconds(t2 - t1);
}

#endif //__UTILS_H__
