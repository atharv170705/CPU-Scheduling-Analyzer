#ifndef MLFQ_H
#define MLFQ_H

#include <vector>
#include <string>
#include "Scheduler.h"

using namespace std;

class MLFQ : public Scheduler {
public:
    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;

    string getName() const override;
};

#endif