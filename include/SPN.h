#ifndef SPN_H
#define SPN_H

#include "Scheduler.h"

class SPN : public Scheduler {
public:
    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;    

    string getName() const override;
};

#endif