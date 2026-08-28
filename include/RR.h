#ifndef RR_H
#define RR_H

#include <vector>
#include <string>
#include "Scheduler.h"

using namespace std;

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