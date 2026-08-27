#ifndef HRRN_H
#define HRRN_H

#include "Scheduler.h"

class HRRN : public Scheduler {

public:

    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;

    string getName() const override;
};

#endif