#include <bits/stdc++.h>
#include "Timeline.h"

using namespace std;

void addExecutionBlock(
    vector<ExecutionBlock>& timeline,
    int processId,
    int startTime,
    int endTime
) {
    if(startTime == endTime) {
        return;
    }

    if(!timeline.empty() && timeline.back().processId == processId && timeline.back().endTime == startTime) {
        timeline.back().endTime = endTime;
        return;
    }

    timeline.push_back({
        processId,
        startTime,
        endTime
    });
}