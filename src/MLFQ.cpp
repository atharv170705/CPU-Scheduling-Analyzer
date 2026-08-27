#include <bits/stdc++.h>
#include "MLFQ.h"
#include "Timeline.h"
#include "MetricsEngine.h"

using namespace std;

ScheduleResult MLFQ::simulate(const vector<Process>& processes) {
    ScheduleResult result;
    
    if(processes.empty()) {
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

    int completed = 0;
    int currentTime = 0;
    int nextProcess = 0;

    // Three priority levels, 0 -> highest, 2 -> lowest

    queue<int> queues[3];

    int quantum[3] = {2, 4, 8};

    vector<int> currentQueue(n, 0);

    while(completed < n) {

        while(nextProcess < n && localProcesses[nextProcess].getArrivalTime() <= currentTime) {
            queues[0].push(nextProcess);
            nextProcess++;
        }

        int selectedQueue = -1;

        for(int level = 0; level < 3; level++) {
            if(!queues[level].empty()) {
                selectedQueue = level;
                break;
            }
        }

        if(selectedQueue == -1) {
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

        int index = queues[selectedQueue].front();
        queues[selectedQueue].pop();

        Process& process = localProcesses[index];
        
        int startTime = currentTime;
        int executionTime = min(quantum[selectedQueue], process.getRemainingTime());

        currentTime += executionTime;

        process.setRemainingTime(process.getRemainingTime() - executionTime);

        addExecutionBlock(
            result.timeline,
            process.getId(),
            startTime,
            currentTime
        );

         while(nextProcess < n && localProcesses[nextProcess].getArrivalTime() <= currentTime) {
            queues[0].push(nextProcess);
            nextProcess++;
         }

         if(process.getRemainingTime() == 0) {
            completed++;
         }
         // Process did not finish.
         else {
            // Demote it to the next queue.
            if(selectedQueue < 2) {
                currentQueue[index] = selectedQueue + 1;
                queues[selectedQueue + 1].push(index);

            }
            else {
                queues[2].push(index);
            }
         }
    }

    MetricsEngine::calculateMetrics(processes, result);

    return result;
}

string MLFQ::getName() const {
    return "MLFQ";
}