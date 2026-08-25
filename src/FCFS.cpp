#include <bits/stdc++.h>
#include "FCFS.h"

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
            result.timeline.push_back({
                -1,
                currentTime,
                process.getArrivalTime()
            });

            currentTime = process.getArrivalTime();
        }

        int startTime = currentTime;
        int completionTime = startTime + process.getBurstTime();

        result.timeline.push_back({
            process.getId(),
            startTime,
            completionTime
        });

        //metrics
        int turnaroundTime = completionTime - process.getArrivalTime();
        int waitingTime = turnaroundTime - process.getBurstTime();
        int responseTime = startTime - process.getArrivalTime();

        result.metrics.push_back({
            process.getId(),
            completionTime,
            turnaroundTime,
            waitingTime,
            responseTime
        });

        currentTime = completionTime;
    }

    return result;
}

string FCFS::getName() const {
    return "FCFS";
}