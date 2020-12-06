#include "processor.h"
#include<string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

  std::string line{};

//draws previous state every time this function is called
  prevuser = user;
  prevnice = nice;
  prevsystem = system;
  previdle = idle;
  previowait = iowait;
  previrq = irq;
  prevsoftirq = softirq;
  prevsteal = steal;

 //measuring later immediate state 
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
linestream>> cpu>>user>>nice>>system>>idle>>iowait>>irq>>softirq>>steal;
  }

// using calculation provided in stackoverflow columns, using later and previous state values.
PrevIdle = previdle + previowait;
Idle = idle + iowait;

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
NonIdle = user + nice + system + irq + softirq + steal;

PrevTotal = PrevIdle + PrevNonIdle;
Total = Idle + NonIdle;

//# differentiate: actual value minus the previous one
totald = Total - PrevTotal;
idled = Idle - PrevIdle;

return float(totald - idled)/totald;

NonIdle= user+nice+system+irq+softirq;
Idle = idle+iowait;
Total = Idle + NonIdle;

return float(Total -Idle)/(Total);

    }
