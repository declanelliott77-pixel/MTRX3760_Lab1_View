// A line-following robot (function-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// Each part of the robot is a struct, and free functions operate on those
// structs by taking them as arguments.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <stdio.h>

//--Consts---------------------------------------------------------------------
const int NumCycles = 4;              // how many cycles the robot runs for
const double BaseSpeed = 0.5;         // forward speed before steering is added

//---SLineSensor---------------------------------------------------------------
// SLineSensor reports how far the robot is off the line. It remembers which
// cycle it is up to so that successive reads walk along the track.
struct SLineSensor
{
  int cycle;              // how many readings have been taken so far
};

//---SController---------------------------------------------------------------
// SController turns an off-line reading into a steering amount. It remembers
// the previous reading so it can respond to how fast the error is changing.
struct SController
{
  double lastError;       // the reading from the previous cycle
};

//---SMotor--------------------------------------------------------------------
// SMotor holds one drive motor's label and its current speed.
struct SMotor
{
  const char* pName;      // the motor's label, e.g. "Left"
  double speed;           // current speed, -1.0 to 1.0
};
//---SBattery--------------------------------------------------------------------
// SBattery holds one battery's label and its current charge level and loses charge every cycle.
struct SBattery{
  const char* pName;      // the battery's label, e.g. "Battery"
  double charge;          // current charge level, 0.0 to 1.0
};

//---Function declarations-----------------------------------------------------
void InitLineSensor( SLineSensor* apSensor );
void InitController( SController* apController );
void InitMotor( SMotor* apMotor, const char* aName );
void InitBattery( SBattery* apBattery, const char* aName );

int ReadLineSensor( SLineSensor* apSensor );
double ComputeSteering( SController* apController, int aError );
void SetMotorSpeed( SMotor* apMotor, double aSpeed );
void LoseBattery( SBattery* apBattery );
int isLow( SBattery* apBattery );

void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor, SBattery* apBattery );
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor );

//---main----------------------------------------------------------------------
// Sets up each part of the robot, then runs it for a number of cycles,
// reporting the motors after each one.
int main()
{
  SLineSensor sensor;
  SController controller;
  SMotor leftMotor;
  SMotor rightMotor;
  SBattery battery;

  InitLineSensor( &sensor );
  InitController( &controller );
  InitMotor( &leftMotor, "Left" );
  InitMotor( &rightMotor, "Right" );
  InitBattery( &battery, "Battery" );

  for( int i = 0; i < NumCycles; ++i )
  {
    UpdateRobot( &sensor, &controller, &leftMotor, &rightMotor, &battery );
    ReportRobot( &leftMotor, &rightMotor );
  }

  return 0;
}

//---InitLineSensor------------------------------------------------------------
// Starts the sensor at the beginning of the track.
void InitLineSensor( SLineSensor* apSensor )
{
  apSensor->cycle = 0;
}

//---InitController------------------------------------------------------------
// Starts the controller with no previous reading.
void InitController( SController* apController )
{
  apController->lastError = 0.0;
}

//---InitMotor-----------------------------------------------------------------
// Gives a motor its label and sets it stopped.
void InitMotor( SMotor* apMotor, const char* aName )
{
  apMotor->pName = aName;
  apMotor->speed = 0.0;
}

//---InitBattery---------------------------------------------------------------
// Gives a battery its label and sets it fully charged.
void InitBattery( SBattery* apBattery, const char* aName ){
  apBattery->pName = aName;
  apBattery->charge = 1.0; // Fully charged
}
//---LoseBattery---------------------------------------------------------------
// Reduces the battery's charge level by 10% each cycle.
void LoseBattery( SBattery* apBattery ){
  apBattery->charge -= 0.1; // Reduce charge by 10%
  if(apBattery->charge < 0.0){
    apBattery->charge = 0.0; // Ensure charge doesn't go below 0, not necessary for assignment but may be needed for A5.
  }
}
//---isLow---------------------------------------------------------------------
// Returns true if the battery is low on charge, ie below 80%. You would replace this with a bool, however that has not been taught yet.
int isLow( SBattery* apBattery ){
  int Result;
  if (apBattery->charge < 0.8)
  {Result = 1; // Battery is low
  }
  else
  {
    Result = 0; // Battery is not low
  }
  return Result; // Return the result to be used to change motor speed.
}
//---ReadLineSensor------------------------------------------------------------
// Returns how far the robot is off the line this cycle. Positive means the
// line is off to one side, negative the other.
int ReadLineSensor( SLineSensor* apSensor )
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ apSensor->cycle ];
  ++apSensor->cycle;

  return reading;
}

//---ComputeSteering-----------------------------------------------------------
// Works out how hard to steer, from how far off the line the robot is and how
// quickly that is changing.
double ComputeSteering( SController* apController, int aError )
{
  double steering = 0.1 * aError + 0.05 * ( aError - apController->lastError );
  apController->lastError = aError;

  return steering;
}

//---SetMotorSpeed-------------------------------------------------------------
// Sets one motor's speed.
void SetMotorSpeed( SMotor* apMotor, double aSpeed )
{
  apMotor->speed = aSpeed;
}

//---UpdateRobot---------------------------------------------------------------
// Runs one cycle: read the sensor, work out the steering, and set both motors.
void UpdateRobot( SLineSensor* apSensor, SController* apController,
                  SMotor* apLeftMotor, SMotor* apRightMotor, SBattery* apBattery )
{
  double speed = BaseSpeed;
  int error = ReadLineSensor( apSensor );
  double steering = ComputeSteering( apController, error );
  if(isLow(apBattery)){ 
    speed = BaseSpeed * 0.5; // Reduce speed by 50% if battery is low
  }
  SetMotorSpeed( apLeftMotor, speed + steering );
  SetMotorSpeed( apRightMotor, speed - steering );
  LoseBattery( apBattery ); // Reduce battery charge at the end of each cycle
}

//---ReportRobot---------------------------------------------------------------
// Prints the state of both of the robot's motors.
void ReportRobot( SMotor* apLeftMotor, SMotor* apRightMotor )
{
  printf( "%s motor %g, %s motor %g\n",
          apLeftMotor->pName, apLeftMotor->speed,
          apRightMotor->pName, apRightMotor->speed );
}
