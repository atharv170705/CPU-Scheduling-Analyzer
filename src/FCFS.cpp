#include <bits/stdc++.h>
#include "FCFS.h"
#include "Timeline.h"
#include "MetricsEngine.h"

using namespace std;

ScheduleResult FCFS::simulate(const vector<Process>& processes) {

    ScheduleResult result;

    if (processes.empty()) {
        return result;
    }

    vector<Process> sortedProcesses = processes;

    sort(sortedProcesses.begin(), sortedProcesses.end(), 
        [](const Process& a, const Process& b) {
            if(a.getArrivalTime() == b.getArrivalTime()) {
                return a.getId() < b.getId();
            }
            return a.getArrivalTime() < b.getArrivalTime();
        }
    );

    int currentTime = 0;

    for(const Process& process : sortedProcesses) {
        // CPU is idle until this process arrives.
        if(currentTime < process.getArrivalTime()) {
            addExecutionBlock(
                result.timeline,
                -1,
                currentTime,
                process.getArrivalTime()
            );

            currentTime = process.getArrivalTime();
        }

        int startTime = currentTime;
        int completionTime = startTime + process.getBurstTime();

        addExecutionBlock(
            result.timeline,
            process.getId(),
            startTime,
            completionTime
        );

        currentTime = completionTime;
    }

    MetricsEngine::calculateMetrics(processes, result);

    return result;
}

string FCFS::getName() const {
    return "FCFS";
}