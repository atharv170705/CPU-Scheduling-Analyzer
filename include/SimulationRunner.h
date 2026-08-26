#ifndef SIMULATION_RUNNER_H
#define SIMULATION_RUNNER_H

#include <vector>
#include <memory>
#include "Scheduler.h"

using namespace std;

class SimulationRunner {
public:
    static vector<ScheduleResult> runSequential(
        const vector<Process>& processes,
        vector<unique_ptr<Scheduler>>& schedulers
    );   

    static vector<ScheduleResult> runConcurrent(
        const vector<Process>& processes,
        vector<unique_ptr<Scheduler>>& schedulers
    );   
};

#endif