#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "ScheduleResult.h"
#include <vector>

using namespace std;

class RecommendationEngine {
public:
    static void rankAlgorithms(
        vector<ScheduleResult>& results
    );
};

#endif