#ifndef PROCESS_H
#define PROCESS_H

class Process {
private:
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;

public:
    Process(int id, int arrivalTime, int burstTime);
    
    int getId() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getRemainingTime() const;

    void setRemainingTime(int remainingTime);
};

#endif