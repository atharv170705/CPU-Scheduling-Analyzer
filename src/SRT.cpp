#include <bits/stdc++.h>
#include "SRT.h"

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

    vector<int> responseTimes(n, -1);

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

            result.timeline.push_back({
                -1,
                currentTime,
                nextArrival
            });

            currentTime = nextArrival;
            continue;
        }

        Process& process = localProcesses[selected];

        // Record response time when the process first gets CPU.
        if(responseTimes[selected] == -1) {
            responseTimes[selected] = currentTime - process.getArrivalTime();
        }

        int startTime = currentTime;
        //execute for exactly one unit of time
        process.setRemainingTime(process.getRemainingTime() - 1);
        currentTime++;

        // If the previous timeline block belongs to the same process,
        // extend it instead of creating a new one-unit block.
        if(!result.timeline.empty() && result.timeline.back().processId == process.getId() && result.timeline.back().endTime == startTime) {
            result.timeline.back().endTime = currentTime;
        }
        else {
            result.timeline.push_back({
                process.getId(),
                startTime,
                currentTime
            });
        }

        if(process.getRemainingTime() == 0) {
            completed++;

            int completionTime = currentTime;
            int turnaroundTime = completionTime - process.getArrivalTime();
            int waitingTime = turnaroundTime - process.getBurstTime();
            int responseTime = responseTimes[selected];

            result.metrics.push_back({
                process.getId(),
                completionTime,
                turnaroundTime,
                waitingTime,
                responseTime
            });
        }
    }

    return result;
}

string SRT::getName() const {
    return "SRT";
}