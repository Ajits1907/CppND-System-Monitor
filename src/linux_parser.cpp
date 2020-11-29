#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >>
        kernel;  // taking the third token which indicates the version no.
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string str,kb;
  string line;
  int i=0;
  long int Total{}, value{},free{};
  std::ifstream filestream(kProcDirectory + kMeminfoFilename) ;
  if(filestream.is_open())
  {
  while(std::getline(filestream,line) && i<2)   // Reading only first 2 lines
  {
  std::istringstream linestream(line);
  while(linestream>>str>>value>>kb)
  {
    if(str== "MemTotal:")
    Total= value;
    else if(str== "MemFree:")
    free= value;
  }
  i++;
}
  }
return float(Total-free)/(Total);
}


// TODO: Read and return the system uptime
long LinuxParser::UpTime() {   
  string line;
  long time;
  std::ifstream filestream(kProcDirectory + kUptimeFilename) ;
  if(filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
     linestream>> time; 
    }
return time; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {};}  // left unused; Processor class made direct call to linux parser

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string str,line;
  int Total{},i=0;
  std::ifstream filestream(kProcDirectory + kStatFilename) ;
  if(filestream.is_open())
  {
  while(std::getline(filestream,line) && i<9)   // Reading only first 9 lines
  {
    if(i==8){
     std::istringstream linestream(line);
     linestream>>str>>Total; 
    }

  i++;
}
  }
return Total;}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
    string str,line;
  int numb,i=0;
  std::ifstream filestream(kProcDirectory + kStatFilename) ;
  if(filestream.is_open())
  {
  while(std::getline(filestream,line) && i<10)   // Reading only first 9 lines
  {
    if(i==9){
     std::istringstream linestream(line);
     linestream>>str>>numb; 
    }

  i++;
}
  }
return numb;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid [[maybe_unused]]) { return 0; }