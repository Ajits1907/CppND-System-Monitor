#include <string>
#include<cmath>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
    string Format::ElapsedTime(long seconds) { 
    
    int HH,MM,SS;
    HH= floor(seconds/3600);
    seconds = seconds- HH*3600;
    MM = floor(seconds/60);
    seconds=seconds-MM*60;
    SS= seconds;
    return  std::to_string(HH) + ":" + std::to_string(MM) + ":" + std::to_string(SS);


    }