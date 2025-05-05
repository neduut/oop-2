#include "timeMeasurement.h"
#include <fstream>  

using namespace std::chrono;

// Constructor with a name
TimeMeasurement::TimeMeasurement(const std::string& name) {
    actionName = name;
}

// Start measurement
void TimeMeasurement::start() {
    startTime = high_resolution_clock::now();
}

// Stop measurement and log the time to file
void TimeMeasurement::stop(std::ofstream& runTimeResults) {
    endTime = high_resolution_clock::now();

    // Log the time directly to the file
    if (runTimeResults.is_open()) {
        runTimeResults << "---> " << actionName << " užtruko: " << getTimeDifference() << " s\n";
    } else {
        std::cerr << "Failed to open file" << std::endl;
    }  
}

// Returns the time difference in seconds
double TimeMeasurement::getTimeDifference() {
    return duration<double>(endTime - startTime).count();
}
