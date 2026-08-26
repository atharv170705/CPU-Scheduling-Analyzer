#include <bits/stdc++.h>
#include "SRT.h"
#include "Timeline.h"
#include "MetricsEngine.h"

using namespace std;

ScheduleResult SRT::simulate(const vector<Process>& processes) {
    ScheduleResult result;

    if(processes.empty()) {
        return result;
    }

    vector<Process> localProcesses = processes;
    
    int n = localProcesses.size();
    int completed = 0;
    int currentTime = 0;

    while(completed < n) {
        int selected = -1;

        // Find the process with the smallest remaining time
        // among all processes that have already arrived.
        for(int i = 0; i < n; i++) {
            if(localProcesses[i].getArrivalTime() <= currentTime && localProcesses[i].getRemainingTime() > 0) {
                if(selected == -1 || localProcesses[i].getRemainingTime() < localProcesses[selected].getRemainingTime()) {
                    selected = i;
                }
                else if(localProcesses[i].getRemainingTime() == localProcesses[selected].getRemainingTime() && localProcesses[i].getArrivalTime() < localProcesses[selected].getArrivalTime()) {
                    selected = i;
                }
            }
        }

        // No process is currently available.
        if(selected == -1) {
            int nextArrival = INT_MAX;
            for(int i = 0; i < n; i++) {
                if(localProcesses[i].getRemainingTime() > 0 && localProcesses[i].getArrivalTime() > currentTime) {
                    nextArrival = min(nextArrival, localProcesses[i].getArrivalTime());
                }
            }

            addExecutionBlock(
                result.timeline,
                -1,
                currentTime,
                nextArrival
            );
    
            currentTime = nextArrival;
            continue;
        }

        Process& process = localProcesses[selected];

        int startTime = currentTime;
        //execute for exactly one unit of time
        process.setRemainingTime(process.getRemainingTime() - 1);
        currentTime++;
        
        addExecutionBlock(
            result.timeline,
            process.getId(),
            startTime,
            currentTime
        );

        if(process.getRemainingTime() == 0) {
            completed++;
        }
    }

    MetricsEngine::calculateMetrics(processes, result);

    return result;
}

string SRT::getName() const {
    return "SRT";
}