#include <bits/stdc++.h>
#include "RecommendationEngine.h"

using namespace std;

static double normalizeLowerBetter(double value, double minValue, double maxValue) {
    if(maxValue == minValue) {
        return 1.0;
    }
    return (maxValue - value) / (maxValue - minValue);
}

void RecommendationEngine::rankAlgorithms(vector<ScheduleResult>& results) {
    if(results.empty()) {
        return;
    }

    double minWaiting = DBL_MAX;
    double maxWaiting = 0.0;

    double minTurnaround = DBL_MAX;
    double maxTurnaround = 0.0;

    double minResponse = DBL_MAX;
    double maxResponse = 0.0;

    for(const ScheduleResult& result : results) {
        minWaiting = min(minWaiting, result.averageWaitingTime);
        maxWaiting = max(maxWaiting, result.averageWaitingTime);

        minTurnaround = min(minTurnaround, result.averageTurnaroundTime);
        maxTurnaround = max(maxTurnaround, result.averageTurnaroundTime);

        minResponse = min(minResponse, result.averageResponseTime);
        maxResponse = max(maxResponse, result.averageResponseTime);
    }

    const double waitingWeight = 0.40;
    const double turnaroundWeight = 0.30;
    const double responseWeight = 0.30;

    for(ScheduleResult& result : results) {
        double waitingScore = normalizeLowerBetter(result.averageWaitingTime, minWaiting, maxWaiting);
        double turnaroundScore = normalizeLowerBetter(result.averageTurnaroundTime, minTurnaround, maxTurnaround);
        double responseScore = normalizeLowerBetter(result.averageResponseTime, minResponse, maxResponse);

        result.score = waitingWeight * waitingScore + turnaroundWeight * turnaroundScore + responseWeight * responseScore;
    }    

    sort(results.begin(), results.end(), 
        [](const ScheduleResult& a, const ScheduleResult& b) {
            return a.score > b.score;
        }
    );
}