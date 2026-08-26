#include <bits/stdc++.h>
#include "SimulationRunner.h"

using namespace std;

vector<ScheduleResult> SimulationRunner::runSequential(
    const vector<Process>& processes,
    vector<unique_ptr<Scheduler>>& schedulers
) {
    vector<ScheduleResult> results;

    for(auto& scheduler : schedulers) {
        ScheduleResult result = scheduler -> simulate(processes);
        results.push_back(result);
    }

    return results;
}


vector<ScheduleResult> SimulationRunner::runConcurrent(
    const vector<Process>& processes,
    vector<unique_ptr<Scheduler>>& schedulers
) {
    vector<ScheduleResult> results;

    queue<int> jobQueue;

    mutex queueMutex;
    mutex resultMutex;

    condition_variable cv;

    bool finishedProducing = false;

    for(int i = 0; i < (int)schedulers.size(); i++) {
        jobQueue.push(i);
    }

    finishedProducing = true;

    auto worker = [&]() -> void {
        while(true) {
            int jobIndex;
            {
                unique_lock<mutex> lock(queueMutex);

                // We're saying: Sleep until either there is a job available OR production has finished.

                // The while loop approach asks: "Under what conditions should I go to sleep (or go back to sleep)?" (Sleep as long as the queue is empty AND we are not finished producing).
                // while (jobQueue.empty() && !finishedProducing) {
                //     cv.wait(lock);
                // }
                //The Lambda approach asks: "Under what conditions am I allowed to wake up and proceed?" (Proceed if the queue is not empty OR we are finished producing).
                cv.wait(
                    lock,
                    [&]() {
                        return !jobQueue.empty() || finishedProducing;
                    }
                );

                if(jobQueue.empty() && finishedProducing) {
                    return;
                }
                
                jobIndex = jobQueue.front();
                jobQueue.pop();
            }

            ScheduleResult result = schedulers[jobIndex] -> simulate(processes);

            {
                lock_guard<mutex> lock(resultMutex);

                results.push_back(result);
            }
        }
    };

    vector<thread> workers;

    unsigned int hardwareThreads = thread::hardware_concurrency();

    if(hardwareThreads == 0) {
        hardwareThreads = 1;
    }

    int workerCount = min((int)schedulers.size(), (int)hardwareThreads);

    for(int i = 0; i < workerCount; i++) {
        workers.emplace_back(worker);
    }

    cv.notify_all();

    for(auto &workerThread : workers) {
        workerThread.join();
    }

    return results;
}