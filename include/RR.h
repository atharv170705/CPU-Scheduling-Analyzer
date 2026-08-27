#ifndef RR_H
#define RR_H

#include "Scheduler.h"

class RR : public Scheduler {
private:
    int quantum;

public:
    RR(int quantum);

    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;

    string getName() const override;
};

#endif