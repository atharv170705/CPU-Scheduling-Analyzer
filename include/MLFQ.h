#ifndef MLFQ_H
#define MLFQ_H

#include "Scheduler.h"

class MLFQ : public Scheduler {

public:

    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;

    string getName() const override;
};

#endif