#include <bits/stdc++.h>
#include "HRRN.h"
#include "Timeline.h"
#include "MetricsEngine.h"

using namespace std;

ScheduleResult HRRN::simulate(const vector<Process>& processes) {
    ScheduleResult result;
    
    if(processes.empty()) {
        return result;
    }

    result.algorithmName = getName();

    vector<Process> localProcesses = processes;
    int n = localProcesses.size();

    int completed = 0;
    int currentTime = 0;

    vector<bool> scheduled(n, false);

    while(completed < n) {
        int selected = -1;

        double highestRatio = -1.0;

        for(int i = 0; i < n; i++) {
            if(!scheduled[i] && localProcesses[i].getArrivalTime() <= currentTime) {
                int waitingTime = currentTime - localProcesses[i].getArrivalTime();
                int burstTime = localProcesses[i].getBurstTime();

                double responseRatio = static_cast<double>(waitingTime + burstTime) / burstTime;

                if(selected == -1 || responseRatio > highestRatio) {
                    selected = i;
                    highestRatio = responseRatio;
                }
                else if(responseRatio == highestRatio && localProcesses[i].getArrivalTime() < localProcesses[selected].getArrivalTime()) {
                    selected = i;
                }
            }
        }

        // CPU is idle if no process is ready.
        if(selected == -1) {
            int nextArrival = INT_MAX;
            for(int i = 0; i < n; i++) {
                if(!scheduled[i] && localProcesses[i].getArrivalTime() > currentTime) {
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
        //run the selected process until completion.
        currentTime += process.getBurstTime();

        addExecutionBlock(
            result.timeline,
            process.getId(),
            startTime,
            currentTime
        );

        process.setRemainingTime(0);

        scheduled[selected] = true;

        completed++;
    }

    MetricsEngine::calculateMetrics(processes, result);

    return result;
}

string HRRN::getName() const {
    return "HRRN";
}