#include <bits/stdc++.h>
#include "Process.h"
#include "Scheduler.h"
#include "FCFS.h"
#include "RoundRobin.h"

using namespace std;

void printResult(const ScheduleResult& result) {

    cout << "\nGantt Timeline:\n";
    // here const means: We're only reading it.
    // const auto& means: Give me a read-only reference to each element without copying it.
    for (const auto& block : result.timeline) {

        if (block.processId == -1) {
            cout << "[IDLE: "
                 << block.startTime
                 << " -> "
                 << block.endTime
                 << "]\n";
        }
        else {
            cout << "[P"
                 << block.processId
                 << ": "
                 << block.startTime
                 << " -> "
                 << block.endTime
                 << "]\n";
        }
    }

    cout << "\nMetrics:\n";

    for (const auto& metric : result.metrics) {

        cout << "P" << metric.processId
             << " | CT: " << metric.completionTime
             << " | TAT: " << metric.turnaroundTime
             << " | WT: " << metric.waitingTime
             << " | RT: " << metric.responseTime
             << '\n';
    }
}

int main() {

    vector<Process> processes = {
        Process(1, 0, 5),
        Process(2, 1, 3),
        Process(3, 2, 2)
    };

    vector<unique_ptr<Scheduler>> schedulers;

    schedulers.push_back(make_unique<FCFS>());
    schedulers.push_back(make_unique<RoundRobin>(2));

    for (auto& scheduler : schedulers) {

        cout << "\n====================\n";
        cout << "Algorithm: "
             << scheduler->getName()
             << '\n';
        cout << "====================\n";

        ScheduleResult result =
            scheduler->simulate(processes);

        printResult(result);
    }

    return 0;
}