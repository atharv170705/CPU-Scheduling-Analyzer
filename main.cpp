#include <bits/stdc++.h>
#include "Process.h"
#include "Scheduler.h"
#include "FCFS.h"
#include "RoundRobin.h"
#include "SRT.h"
#include "SimulationRunner.h"

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

    cout << fixed << setprecision(2);

    cout << "\nPerformance Summary:\n";

    cout << "Average Waiting Time    : "
        << result.averageWaitingTime << '\n';

    cout << "Average Turnaround Time : "
        << result.averageTurnaroundTime << '\n';

    cout << "Average Response Time   : "
        << result.averageResponseTime << '\n';

    cout << "CPU Utilization         : "
        << result.cpuUtilization << "%\n";

    cout << "Throughput              : "
        << result.throughput
        << " processes/unit time\n";
}

int main() {

    vector<Process> processes = {
        Process(1, 0, 5),
        Process(2, 10, 3),
        Process(3, 12, 2)
    };

    vector<unique_ptr<Scheduler>> schedulers;

    schedulers.push_back(make_unique<FCFS>());
    schedulers.push_back(make_unique<RoundRobin>(2));
    schedulers.push_back(make_unique<SRT>());

    vector<ScheduleResult> sequentialResult = SimulationRunner::runSequential(processes, schedulers);

    vector<ScheduleResult> concurrentResults = SimulationRunner::runConcurrent(processes, schedulers);

    for(const auto& result : sequentialResult) {

        cout << "\n====================\n";
        cout << "Algorithm: "
            << result.algorithmName
            << '\n';
        cout << "====================\n";

        printResult(result);
    }

    cout << "\n\n===== CONCURRENT RESULTS =====\n";

    for(const auto& result : concurrentResults) {

        cout << "\n====================\n";
        cout << "Algorithm: "
            << result.algorithmName
            << '\n';
        cout << "====================\n";

        printResult(result);
    }

    return 0;
}