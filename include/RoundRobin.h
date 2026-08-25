#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "Scheduler.h"

class RoundRobin : public Scheduler {
private:
    int quantum;

public:
    RoundRobin(int quantum);

    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;

    string getName() const override;
};

#endif