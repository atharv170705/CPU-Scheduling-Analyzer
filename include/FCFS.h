#ifndef FCFS_H
#define FCFS_H

#include "Scheduler.h"

class FCFS : public Scheduler {
public:
    ScheduleResult simulate(
        const vector<Process>& processes 
    ) override;
    //override tells compiler: I intend for this function to override a virtual function from the parent class.
    //So override is basically a safety check for inheritance/polymorphism.
    string getName() const override;
};

#endif