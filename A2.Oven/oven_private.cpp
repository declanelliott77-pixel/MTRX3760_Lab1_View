// An oven temperature model (encapsulated version)
//
// This program models two ovens that warm up in steps and warn if they
// overheat. Each oven's data is private, and main() works through meaningful
// functions rather than touching the temperatures directly.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//---COven---------------------------------------------------------------------
// COven holds an oven's name and current temperature. The temperature is
// private: callers change and inspect it only through the functions below.
class COven
{
  public:
    // Creates an oven with the given name, at room temperature.
    COven( const std::string& aName );

    // WarmUp raises the oven's temperature by one step.
    void WarmUp();

    // IsOverheating reports whether the oven has passed its safe limit.
    bool IsOverheating();

    // Report prints the oven's name and current temperature.
    void Report();

  private:
    std::string mName;       // the oven's label, e.g. "Reflow oven"
    int mTemperatureC;       // current temperature, in whole degrees Celsius
};

//---main----------------------------------------------------------------------
// Sets up two ovens, warms each in steps, checks each for overheating, and
// reports both.
int main()
{
  COven ReflowOven( "Reflow oven" );
  COven CuringOven( "Curing oven" );

  for( int i = 0; i < 5; ++i )
    ReflowOven.WarmUp();

  for( int i = 0; i < 8; ++i )
    CuringOven.WarmUp();

  if( ReflowOven.IsOverheating() )
    std::cout << "Warning: oven is overheating!" << std::endl;

  if( CuringOven.IsOverheating() )
    std::cout << "Warning: oven is overheating!" << std::endl;

  ReflowOven.Report();
  CuringOven.Report();

  return 0;
}

//---COven Implementation------------------------------------------------------
COven::COven( const std::string& aName )
  : mName( aName ),
    mTemperatureC( 20 )                 // start at room temperature
{
}
//---
void COven::WarmUp()
{
  mTemperatureC += 1;                   // warm up by one degree
}
//---
bool COven::IsOverheating()
{
  return mTemperatureC >= 250;          // overheating limit is 250 C
}
//---
void COven::Report()
{
  std::cout << mName << " is at " << mTemperatureC << "C" << std::endl;
}
