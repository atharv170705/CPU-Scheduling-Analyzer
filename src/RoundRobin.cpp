#include <bits/stdc++.h>
#include "RoundRobin.h"
#include "Timeline.h"
#include "MetricsEngine.h"

using namespace std;

RoundRobin::RoundRobin(int quantum) : quantum(quantum) {}

ScheduleResult RoundRobin::simulate(const vector<Process>& processes) {
    ScheduleResult result;
    
    if (processes.empty()) {
        return result;
    }

    result.algorithmName = getName();

    vector<Process> localProcesses = processes;
    int n = localProcesses.size();

    sort(localProcesses.begin(), localProcesses.end(),
        [](const Process& a, const Process& b) {
            if (a.getArrivalTime() == b.getArrivalTime()) {
                return a.getId() < b.getId();
            }
            return a.getArrivalTime() < b.getArrivalTime();
        }
    );

    queue<int> readyQueue;

    int currentTime = 0;
    int nextProcess = 0;
    int completed = 0;

    while(completed < n) {
        // Add every process that has arrived.
        while(nextProcess < n && localProcesses[nextProcess].getArrivalTime() <= currentTime) {
            readyQueue.push(nextProcess);
            nextProcess++;
        }

        // CPU is idle if no process is ready.
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

        int index = readyQueue.front();
        readyQueue.pop();

        Process& process = localProcesses[index];

        int startTime = currentTime;
        int executionTime = min(quantum, process.getRemainingTime());

        currentTime += executionTime;

        process.setRemainingTime(process.getRemainingTime() - executionTime);

       addExecutionBlock(
            result.timeline,
            process.getId(),
            startTime,
            currentTime
       );

        // Add processes that arrived during this time slice.
        while(nextProcess < n && localProcesses[nextProcess].getArrivalTime() <= currentTime) {
            readyQueue.push(nextProcess);
            nextProcess++;
        }

        if(process.getRemainingTime() > 0) {
            readyQueue.push(index);
        }
        else {
            completed++;
        }
    }

    MetricsEngine::calculateMetrics(processes, result);

    return result;
}    

string RoundRobin::getName() const {
    return "Round Robin";
}