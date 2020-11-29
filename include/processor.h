#ifndef PROCESSOR_H
#define PROCESSOR_H

#include<string>
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 std::string cpu{};
 int user{},nice{},system{},idle{},iowait{},irq{},softirq{},steal{}; //present state

int prevuser,prevnice,prevsystem,previdle,previowait,previrq,prevsoftirq,prevsteal; //previous state

int PrevIdle,PrevNonIdle, NonIdle, Idle,PrevTotal, Total; //Calculation as per suggeste forum for CPU time calc. on stack overflow
int totald, idled;
};

#endif