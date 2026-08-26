#ifndef TIMELINE_H
#define TIMELINE_H

#include <vector>
#include "ScheduleResult.h"

using namespace std;

void addExecutionBlock(
    vector<ExecutionBlock>& timeline,
    int processId,
    int startTime,
    int endTime
);

#endif