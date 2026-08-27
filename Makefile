CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
THREADFLAGS = -pthread

TARGET = scheduler
BENCHMARK = benchmark

SOURCES = main.cpp \
          src/Process.cpp \
          src/FCFS.cpp \
          src/RR.cpp \
          src/SRT.cpp \
          src/SPN.cpp \
          src/HRRN.cpp \
          src/MLFQ.cpp \
          src/Timeline.cpp \
          src/MetricsEngine.cpp \
          src/SimulationRunner.cpp \
          src/RecommendationEngine.cpp

BENCHMARK_SOURCES = benchmark.cpp \
                    src/Process.cpp \
                    src/FCFS.cpp \
                    src/RR.cpp \
                    src/SRT.cpp \
                    src/SPN.cpp \
                    src/HRRN.cpp \
                    src/MLFQ.cpp \
                    src/Timeline.cpp \
                    src/MetricsEngine.cpp \
                    src/SimulationRunner.cpp          

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(THREADFLAGS) $(SOURCES) -o $(TARGET)

$(BENCHMARK): $(BENCHMARK_SOURCES)
	$(CXX) $(CXXFLAGS) $(THREADFLAGS) -O2 $(BENCHMARK_SOURCES) -o $(BENCHMARK)

clean:
	rm -f $(TARGET) $(BENCHMARK)