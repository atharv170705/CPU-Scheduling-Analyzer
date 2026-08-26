#include <bits/stdc++.h>
#include "RoundRobin.h"

using namespace std;

RoundRobin::RoundRobin(int quantum) : quantum(quantum) {}

ScheduleResult RoundRobin::simulate(const vector<Process>& processes) {
    ScheduleResult result;
    
    if (processes.empty()) {
        return result;
    }

    vector<Process> localProcesses = processes;
    int processesSize = (int)localProcesses.size();

    // first time process got CPU - arrival time
    vector<int> responseTimes(processesSize, -1);

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

    while(completed < processesSize) {
        // Add every process that has arrived.
        while(nextProcess < processesSize && localProcesses[nextProcess].getArrivalTime() <= currentTime) {
            readyQueue.push(nextProcess);
            nextProcess++;
        }

        // CPU is idle if no process is ready.
        if(readyQueue.empty()) {
            if(nextProcess < processesSize) {
                int nextArrival = localProcesses[nextProcess].getArrivalTime();
                result.timeline.push_back({
                    -1,
                    currentTime,
                    nextArrival
                });
            }
            continue;
        }

        int index = readyQueue.front();
        readyQueue.pop();

        Process& process = localProcesses[index];

        int startTime = currentTime;
        int executionTime = min(quantum, process.getRemainingTime());

        if(responseTimes[index] == -1) {
            responseTimes[index] = startTime - process.getArrivalTime();
        }

        currentTime += executionTime;

        process.setRemainingTime(process.getRemainingTime() - executionTime);

        result.timeline.push_back({
            process.getId(),
            startTime,
            currentTime
        });

        // Add processes that arrived during this time slice.
        while(nextProcess < processesSize && localProcesses[nextProcess].getArrivalTime() <= currentTime) {
            readyQueue.push(nextProcess);
            nextProcess++;
        }

        if(process.getRemainingTime() > 0) {
            readyQueue.push(index);
        }
        else {
            completed++;

            int completionTime = currentTime;
            int turnaroundTime = completionTime - process.getArrivalTime();
            int waitingTime = turnaroundTime - process.getBurstTime();

            int responseTime = responseTimes[index];

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

string RoundRobin::getName() const {
    return "Round Robin";
}