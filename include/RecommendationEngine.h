#ifndef RECOMMENDATION_ENGINE_H
#define RECOMMENDATION_ENGINE_H

#include "ScheduleResult.h"

class RecommendationEngine {
public:
    static void rankAlgorithms(
        vector<ScheduleResult>& results
    );
};

#endif