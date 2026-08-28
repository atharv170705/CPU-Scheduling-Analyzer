#ifndef SPN_H
#define SPN_H

#include <vector>
#include <string>
#include "Scheduler.h"

using namespace std;

class SPN : public Scheduler {
public:
    ScheduleResult simulate(
        const vector<Process>& processes
    ) override;    

    string getName() const override;
};

#endif