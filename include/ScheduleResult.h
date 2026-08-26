#ifndef SCHEDULE_RESULT_H
#define SCHEDULE_RESULT_H

#include <vector>

struct ExecutionBlock {
    int processId;
    int startTime;
    int endTime;
};

struct ProcessMetrics {
    int processId;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

struct ScheduleResult {
    vector<ExecutionBlock> timeline;
    vector<ProcessMetrics> metrics;

    double averageWaitingTime = 0.0;
    double averageTurnaroundTime = 0.0;
    double averageResponseTime = 0.0;

    double cpuUtilization = 0.0;
    double throughput = 0.0;
};

#endif