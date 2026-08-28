#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>
#include "Process.h"
#include "ScheduleResult.h"

using namespace std;

class Scheduler {
public:
    // virtual means: means this function can be overridden by derived classes, and C++ can choose the correct implementation at runtime. (runtime polymorphism)
    virtual ScheduleResult simulate(
        const vector<Process>& processes
    ) = 0; 
    // () = 0 means: Every concrete scheduler MUST provide its own implementation.
    virtual string getName() const = 0;

    virtual ~Scheduler() = default;
};

#endif