#include <bits/stdc++.h>
#include "MetricsEngine.h"

using namespace std;

void MetricsEngine::calculateMetrics(
    const vector<Process>& processes,
    ScheduleResult& result
) {
    unordered_map<int, int> arrivalTime;
    unordered_map<int, int> burstTime;
    unordered_map<int, int> firstStartTime;

    for(const Process& process : processes) {
        arrivalTime[process.getId()] = process.getArrivalTime();
        burstTime[process.getId()] = process.getBurstTime();
        firstStartTime[process.getId()] = -1;
    }

    unordered_map<int, int> completionTime;

    for(const auto& block : result.timeline) {
        if(block.processId == -1) {
            continue;
        }

        int processId = block.processId;

        if(firstStartTime[processId] == -1) {
            firstStartTime[processId] = block.startTime;
        }

        completionTime[processId] = block.endTime;
    }

    result.metrics.clear();

    for(const Process& process : processes) {
        int id = process.getId();

        int ct = completionTime[id];
        int tat = ct - arrivalTime[id];
        int wt = tat - burstTime[id];
        int rt = firstStartTime[id] - arrivalTime[id];

        result.metrics.push_back({
            id,
            ct,
            tat,
            wt,
            rt
        });
    } 

    calculateSummary(processes, result);
}

void MetricsEngine::calculateSummary(
    const vector<Process>& processes,
    ScheduleResult& result
) {
    if(processes.empty()) {
        return;
    }

    double totalWaitingTime = 0.0;
    double totalTurnaroundTime = 0.0;
    double totalResponseTime = 0.0;

    for(const auto &metric : result.metrics) {
        totalWaitingTime += metric.waitingTime;
        totalTurnaroundTime += metric.turnaroundTime;
        totalResponseTime += metric.responseTime;
    }

    int n = processes.size();

    result.averageWaitingTime = totalWaitingTime / n;
    result.averageTurnaroundTime = totalTurnaroundTime / n;
    result.averageResponseTime = totalResponseTime / n;

    int totalBurstTime = 0;

    for(const Process& process : processes) {
        totalBurstTime += process.getBurstTime();
    }

    int firstArrival = INT_MAX;
    int lastCompletion = 0;

    for(const Process& process : processes) {
        firstArrival = min(firstArrival, process.getArrivalTime());
    }

    for(const auto& metric : result.metrics) {
        lastCompletion = max(lastCompletion, metric.completionTime);
    }

    int totalElapsedTime = lastCompletion - firstArrival;

    if(totalElapsedTime > 0) {
        result.cpuUtilization = (double)totalBurstTime / totalElapsedTime * 100.0;
        result.throughput = (double)n / totalElapsedTime;
    }
}