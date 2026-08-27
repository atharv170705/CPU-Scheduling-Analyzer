#include <bits/stdc++.h>
#include "SPN.h"
#include "Timeline.h"
#include "MetricsEngine.h"

using namespace std;

ScheduleResult SPN::simulate(const vector<Process>& processes) {
    ScheduleResult result;

    if(processes.empty()) {
        return result;
    }

    result.algorithmName = getName();

    vector<Process> localProcesses = processes;
    int n = localProcesses.size();

    int completed = 0;
    int currentTime = 0;
    int nextProcess = 0;

    sort(localProcesses.begin(), localProcesses.end(),
        [](const Process& a, const Process& b) {
            if(a.getArrivalTime() == b.getArrivalTime()) {
                return a.getId() < b.getId();
            }
            return a.getArrivalTime() < b.getArrivalTime();
        }
    );

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> readyQueue;

    while(completed < n) {
        
        while(nextProcess < n && localProcesses[nextProcess].getArrivalTime() <= currentTime) {
            readyQueue.push({localProcesses[nextProcess].getBurstTime(), nextProcess});
            nextProcess++;
        }

        if(readyQueue.empty()) {
            if(nextProcess < n) {
                int nextArrival = localProcesses[nextProcess].getArrivalTime();
                addExecutionBlock(
                    result.timeline,
                    -1,
                    currentTime,
                    nextArrival
                );
                currentTime = nextArrival;
            }
            continue;
        }

        int index = readyQueue.top().second;
        readyQueue.pop();

        Process& process = localProcesses[index];

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

        completed++;
    }

    MetricsEngine::calculateMetrics(processes, result);

    return result;
}

string SPN::getName() const {
    return "SPN";
}