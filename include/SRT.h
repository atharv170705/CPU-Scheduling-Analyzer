#ifndef SRT_H
#define SRT_H

#include <vector>
#include <string>
#include "Scheduler.h"

using namespace std;

class SRT : public Scheduler {
public:
    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;

    string getName() const override;
};

#endif