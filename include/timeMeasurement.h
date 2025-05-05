#pragma once
#include <chrono>
#include <iostream>
#include <fstream>  

class TimeMeasurement {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    std::string actionName;

public:
    // Constructor with an action name
    TimeMeasurement(const std::string& name);

    // Start measurement
    void start();

    // Stop measurement and log the time to file
    void stop(std::ofstream& runTimeResults);

    // Get time difference (seconds)
    double getTimeDifference();

    // Getter for action name (optional)
    std::string getActionName() const { return actionName; }
};

