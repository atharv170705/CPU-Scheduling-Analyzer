#include "Process.h"

Process::Process(int id, int arrivalTime, int burstTime)
    : id(id),
    arrivalTime(arrivalTime),
    burstTime(burstTime),
    remainingTime(burstTime) {

    }

// Process::Process(int id, int arrivalTime, int burstTime) {
//     this->id = id;
//     this->arrivalTime = arrivalTime;
//     this->burstTime = burstTime;
//     this->remainingTime = burstTime;
// }


// The :: is the scope resolution operator.
// means: "This function belongs to the Process class."

// here const means: This member function promises not to modify the Process object.
// also say we have const Process p(1, 0, 8); to do p.getId() we need to make it const
int Process::getId() const {
    return id;
}

int Process::getArrivalTime() const {
    return arrivalTime;
}

int Process::getBurstTime() const {
    return burstTime;
}

int Process::getRemainingTime() const {
    return remainingTime;
}

void Process::setRemainingTime(int remainingTime) {
    this -> remainingTime = remainingTime;
}