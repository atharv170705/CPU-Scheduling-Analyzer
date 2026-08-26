#ifndef METRICS_ENGINE_H
#define METRICS_ENGINE_H

#include <vector>
#include "Process.h"
#include "ScheduleResult.h"

using namespace std;

class MetricsEngine {
public:
    // static means: we don't need a MetricsEngine object to call it
    static void calculateMetrics(
        const vector<Process>& processes,
        ScheduleResult& result
    );

private:
    static void calculateSummary(
        const vector<Process>& processes,
        ScheduleResult& result
    );    
};

#endif