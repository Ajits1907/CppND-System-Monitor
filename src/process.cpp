#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) :pid_(pid){ 
}; //constructor initialization

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  long utime, stime, cutime, cstime;
  long starttime, total_time = 0;
  vector<string> data = LinuxParser::CpuUtilization(pid_);

// following method obtained from stack overflow forum as directed in Udacity projects.

  long int uptime = LinuxParser::UpTime();
  long int hertz = sysconf(_SC_CLK_TCK);
  utime = std::stoi(data[13]);
  stime = std::stoi(data[14]);
  cutime = std::stoi(data[15]);
  cstime = std::stoi(data[16]);
  starttime = std::stoi(data[21]);

  total_time = utime + stime;
  total_time = total_time + cutime + cstime;
  long seconds = uptime - (starttime / hertz);
  cpu_usage = ((total_time / hertz) / float(seconds));
  return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() {
  string ram = LinuxParser::Ram(pid_);
  long ram1 = (std::stoi(ram))/1024;
  ram = std::to_string(ram1);
  return ram;
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  vector<string> data = LinuxParser::CpuUtilization(pid_);
  long starttime = (std::stoi(data[21]))/sysconf(_SC_CLK_TCK);
  return starttime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a ) const {
  
  return cpu_usage < a.cpu_usage;
  //return true;
}