#include <bits/stdc++.h>

#include "Process.h"
#include "Scheduler.h"
#include "FCFS.h"
#include "RoundRobin.h"
#include "SRT.h"
#include "SimulationRunner.h"

using namespace std;
using namespace chrono;

vector<Process> generateWorkload(
    int processCount,
    int maxBurstTime,
    int maxArrivalTime
) {
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

vector<unique_ptr<Scheduler>> createSchedulers(int jobCount) {
    vector<unique_ptr<Scheduler>> schedulers;

    for(int i = 0; i < jobCount; i++) {
        if(i % 3 == 0) {
            schedulers.push_back(make_unique<FCFS>());
        }
        else if(i % 3 == 1) {
            int quantum = 2 + (i % 5);
            schedulers.push_back(make_unique<RoundRobin>(2));
        }
        else {
            schedulers.push_back(make_unique<SRT>());
        }
    }

    return schedulers;
}

double measureSequential(const vector<Process>& processes, int jobCount) {
    auto schedulers = createSchedulers(jobCount);

    auto start = high_resolution_clock::now();
    auto results = SimulationRunner::runSequential(processes, schedulers);
    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

double measureConcurrent(const vector<Process>& processes, int jobCount) {
    auto schedulers = createSchedulers(jobCount);

    auto start = high_resolution_clock::now();
    auto results = SimulationRunner::runConcurrent(processes, schedulers);
    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

double calculateMedian(vector<double> values) {
    sort(values.begin(), values.end());
    int n = values.size();
    if(n % 2 == 1) {
        return values[n / 2];
    }
    return (values[n / 2 - 1] + values[n / 2]) / 2.0;
}

void runBenchmark(int processCount, int jobCount, int trials) {
    const int MAX_BURST_TIME = 200;
    const int MAX_ARRIVAL_TIME = 500;

    vector<Process> processes = generateWorkload(processCount, MAX_BURST_TIME, MAX_ARRIVAL_TIME);

    vector<double> sequentialTimes;
    vector<double> concurrentTimes;

    for(int trial = 0; trial < trials; trial++) {
        int seqTime = measureSequential(processes, jobCount);
        int conTime = measureConcurrent(processes, jobCount);

        sequentialTimes.push_back(seqTime);
        concurrentTimes.push_back(conTime);
    }

    double sequentialMedian = calculateMedian(sequentialTimes);

    double concurrentMedian = calculateMedian(concurrentTimes);
    
    double speedup = sequentialMedian / concurrentMedian;

    double runtimeReduction = (sequentialMedian - concurrentMedian) / sequentialMedian * 100.0;

    cout << fixed << setprecision(2);

    cout << "Processes: "
         << processCount << '\n';

    cout << "Jobs: "
         << jobCount << '\n';

    cout << "Sequential median: "
         << sequentialMedian
         << " ms\n";

    cout << "Concurrent median: "
         << concurrentMedian
         << " ms\n";

    cout << "Speedup: "
         << speedup
         << "x\n";

    cout << "Runtime reduction: "
         << runtimeReduction
         << "%\n";

    cout << "-----------------------------\n";
}

int main() {
    
    cout << "Hardware threads: "
         << thread::hardware_concurrency()
         << "\n\n";

    const int JOB_COUNT = 12;
    const int TRIALS = 5;

    vector<int> processCounts = {
        100,
        200,
        500,
        1000
    };

    for(int processCount : processCounts) {

        runBenchmark(
            processCount,
            JOB_COUNT,
            TRIALS
        );
    }

    return 0;
}