#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

//#include "process.h"
//#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
pids_ = LinuxParser::Pids() ;

for(size_t i=0; i< pids_.size();i++){
    Process process(pids_[i]);

    processes_.push_back(process);
}

      std::sort(processes_.begin(), processes_.end());  //use operator overloading to compare
      std::reverse(std::begin(processes_), std::end(processes_));
return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem();  //directly return without storing in member attributes
 }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }