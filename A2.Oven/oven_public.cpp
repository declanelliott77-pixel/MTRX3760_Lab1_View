// An oven temperature model (public-data version)
//
// This program models two ovens that warm up in steps and warn if they
// overheat. Each oven's data is stored in public member variables, and main()
// reads and changes the temperatures directly.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>
#include <cmath>

//---COven---------------------------------------------------------------------
// COven holds an oven's name and current temperature. Both members are public,
// so any code can read or change them directly.
class COven
{
  public:
    std::string mName;       // the oven's label, e.g. "Reflow oven"
    float mTemperatureC;       //  current temperature as a float to be stored in tenths of a degree
};

//---main----------------------------------------------------------------------
// Sets up two ovens, warms each in one-degree steps, checks each for
// overheating, and reports both. Every step reaches into the ovens' data
// directly.
int main()
{
  COven ReflowOven;
  ReflowOven.mName = "Reflow oven";
  ReflowOven.mTemperatureC = 20;            // start at room temperature
  ReflowOven.mTemperatureC = std::round( ReflowOven.mTemperatureC * 10 ) / 10 ;  // add this line to round to the tenth degree

  COven CuringOven;
  CuringOven.mName = "Curing oven";
  CuringOven.mTemperatureC = 20;            // start at room temperature
  CuringOven.mTemperatureC = std::round( CuringOven.mTemperatureC * 10 ) / 10 ;  // added this line to round to the tenth degree

  for( int i = 0; i < 5; ++i )
    ReflowOven.mTemperatureC = std::round( (ReflowOven.mTemperatureC + 1) * 10 ) / 10 ; // modified this line so that the increment is rounded to a tenth of a degree.

  for( int i = 0; i < 8; ++i )
    CuringOven.mTemperatureC = std::round( (CuringOven.mTemperatureC + 1) * 10 ) / 10 ; // modified this line so that the increment is rounded to a tenth of a degree.

  if( ReflowOven.mTemperatureC >= 250 )     // overheating limit is 250 C
    std::cout << "Warning: oven is overheating!" << std::endl;

  if( CuringOven.mTemperatureC >= 250 )     // overheating limit is 250 C
    std::cout << "Warning: oven is overheating!" << std::endl;

  std::cout << ReflowOven.mName << " is at "
            << ReflowOven.mTemperatureC << "C" << std::endl;

  std::cout << CuringOven.mName << " is at "
            << CuringOven.mTemperatureC << "C" << std::endl;

  return 0;
}
