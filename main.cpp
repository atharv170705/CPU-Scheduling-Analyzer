#include <bits/stdc++.h>
#include "Process.h"
#include "Scheduler.h"
#include "FCFS.h"
#include "RR.h"
#include "SRT.h"
#include "SPN.h"
#include "HRRN.h"
#include "MLFQ.h"
#include "SimulationRunner.h"
#include "RecommendationEngine.h"

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
        Process(1, 0, 8),
        Process(2, 1, 4),
        Process(3, 2, 3)
    };

    // we use unique_ptr because: No manual delete
    // if we do Scheduler* scheduler = new FCFS(); then we'll have to manually delete
    vector<unique_ptr<Scheduler>> schedulers;

    schedulers.push_back(make_unique<FCFS>());
    schedulers.push_back(make_unique<RR>(2));
    schedulers.push_back(make_unique<SRT>());
    schedulers.push_back(make_unique<SPN>());
    schedulers.push_back(make_unique<HRRN>());
    schedulers.push_back(make_unique<MLFQ>());

    vector<ScheduleResult> sequentialResult = SimulationRunner::runSequential(processes, schedulers);

    // vector<ScheduleResult> concurrentResults = SimulationRunner::runConcurrent(processes, schedulers);

    RecommendationEngine::rankAlgorithms(sequentialResult);

    for(const auto& result : sequentialResult) {

        cout << "\n====================\n";
        cout << "Algorithm: "
            << result.algorithmName
            << '\n';
        cout << "====================\n";

        printResult(result);
    }

    cout << "\n====================\n";
    cout << "Recommendation Ranking\n";
    cout << "====================\n\n";

    for(int i = 0; i < (int)sequentialResult.size(); i++) {

        cout << i + 1 << ". "
            << sequentialResult[i].algorithmName
            << " | Score: "
            << fixed << setprecision(3)
            << sequentialResult[i].score
            << '\n';
    }

    if(!sequentialResult.empty()) {

        cout << "\nRecommended Algorithm: "
            << sequentialResult[0].algorithmName
            << '\n';
    }
    // cout << "\n\n===== CONCURRENT RESULTS =====\n";

    // for(const auto& result : concurrentResults) {

    //     cout << "\n====================\n";
    //     cout << "Algorithm: "
    //         << result.algorithmName
    //         << '\n';
    //     cout << "====================\n";

    //     printResult(result);
    // }

    return 0;
}