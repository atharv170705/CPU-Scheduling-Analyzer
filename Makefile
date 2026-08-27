CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = scheduler

SOURCES = main.cpp \
          src/Process.cpp \
          src/FCFS.cpp \
          src/RoundRobin.cpp \
          src/SRT.cpp \
          src/SPN.cpp \
          src/HRRN.cpp \
          src/MLFQ.cpp \
          src/Timeline.cpp \
          src/MetricsEngine.cpp \
          src/SimulationRunner.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)