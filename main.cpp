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

void printRanking(vector<ScheduleResult> &results) {
    RecommendationEngine::rankAlgorithms(results);
    
    cout << "\n====================\n";
    cout << "Recommendation Ranking\n";
    cout << "====================\n\n";

    for(int i = 0; i < (int)results.size(); i++) {

        cout << i + 1 << ". "
            << results[i].algorithmName
            << " | Score: "
            << fixed << setprecision(3)
            << results[i].score
            << '\n';
    }

    if(!results.empty()) {

        cout << "\nRecommended Algorithm: "
            << results[0].algorithmName
            << '\n';
    }
}

void printSequential(vector<Process>& processes, vector<unique_ptr<Scheduler>>& schedulers) {
    vector<ScheduleResult> sequentialResult = SimulationRunner::runSequential(processes, schedulers);

    cout << "\n\n===== SEQUENTIAL RESULTS =====\n";

    for(const auto& result : sequentialResult) {

        cout << "\n====================\n";
        cout << "Algorithm: "
            << result.algorithmName
            << '\n';
        cout << "====================\n";

        printResult(result);
    }

    printRanking(sequentialResult);
}

void printConcurrent(vector<Process>& processes, vector<unique_ptr<Scheduler>>& schedulers) {
    vector<ScheduleResult> concurrentResults = SimulationRunner::runConcurrent(processes, schedulers);

    cout << "\n\n===== CONCURRENT RESULTS =====\n";

    for(const auto& result : concurrentResults) {

        cout << "\n====================\n";
        cout << "Algorithm: "
            << result.algorithmName
            << '\n';
        cout << "====================\n";

        printResult(result);
    }

    printRanking(concurrentResults);
}

vector<Process> generateWorkload( int processCount, int maxBurstTime, int maxArrivalTime) {
    vector<Process> processes;
    processes.reserve(processCount);

    mt19937 generator(42);

    uniform_int_distribution<int> burstDistribution(1, maxBurstTime);
    uniform_int_distribution<int> arrivalDistribution(0, maxArrivalTime);

    for(int i = 0; i < processCount; i++) {
        int id = i + 1;
        int arrivalTime = arrivalDistribution(generator);
        int burstTime = burstDistribution(generator);

        processes.emplace_back(id, arrivalTime, burstTime);
    }

    return processes;
}

vector<Process> customProcesses() {
    vector<Process> processes = {
        Process(1, 0, 5),
        Process(2, 1, 3),
        Process(3, 2, 4),
        Process(4, 3, 2),
        Process(5, 15, 6),
        Process(6, 16, 3),
        Process(7, 18, 5),
        Process(8, 25, 2)
    };

    return processes;
}

vector<unique_ptr<Scheduler>> createSchedulers() {

     // we use unique_ptr because: No manual delete
    // if we do Scheduler* scheduler = new FCFS(); then we'll have to manually delete
    vector<unique_ptr<Scheduler>> schedulers;

    schedulers.push_back(make_unique<FCFS>());
    schedulers.push_back(make_unique<RR>(2));
    schedulers.push_back(make_unique<SRT>());
    schedulers.push_back(make_unique<SPN>());
    schedulers.push_back(make_unique<HRRN>());
    schedulers.push_back(make_unique<MLFQ>());

    return schedulers;
}

int main() {

    const int PROCESS_COUNT = 10;
    const int MAX_BURST_TIME = 200;
    const int MAX_ARRIVAL_TIME = 500;

    // vector<Process> processes = generateWorkload(PROCESS_COUNT, MAX_BURST_TIME, MAX_ARRIVAL_TIME);
    vector<Process> processes = customProcesses();
    vector<unique_ptr<Scheduler>> schedulers = createSchedulers();

    printConcurrent(processes, schedulers);

    return 0;
}