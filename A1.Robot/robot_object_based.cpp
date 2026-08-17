// A line-following robot (object-based version)
//
// This program models a robot that follows a line. Each cycle the robot reads
// its line sensor, works out how hard to steer, and sets its two drive motors.
// Each part of the robot is a class, and a CRobot holds those parts and puts
// them to work.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>


//--Consts---------------------------------------------------------------------
const int NumCycles = 4;              // how many cycles the robot runs for
const double BaseSpeed = 0.5;         // forward speed before steering is added

//---CLineSensor---------------------------------------------------------------
// A CLineSensor reports how far the robot is off the line. It remembers which
// cycle it is up to so that successive reads walk along the track.
class CLineSensor
{
  public:
    // Creates a sensor at the beginning of the track.
    CLineSensor();

    // Read returns how far the robot is off the line this cycle. Positive
    // means the line is off to one side, negative the other.
    int Read();

  private:
    int mCycle;             // how many readings have been taken so far
};

//---CController---------------------------------------------------------------
// A CController turns an off-line reading into a steering amount. It remembers
// the previous reading so it can respond to how fast the error is changing.
class CController
{
  public:
    // Creates a controller with no previous reading.
    CController();

    // ComputeSteering works out how hard to steer, from how far off the line
    // the robot is and how quickly that is changing.
    double ComputeSteering( int aError );

  private:
    double mLastError;      // the reading from the previous cycle
};

//---CMotor--------------------------------------------------------------------
// A CMotor is a single drive motor with a label and a current speed.
class CMotor
{
  public:
    // Creates a motor with the given label, stopped.
    CMotor( const std::string& aName );

    // SetSpeed sets the motor's speed.
    void SetSpeed( double aSpeed );

    // Report prints the motor's label and current speed.
    void Report();

  private:
    std::string mName;      // the motor's label, e.g. "Left"
    double mSpeed;          // current speed, -1.0 to 1.0
};
//-- CBattery--------------------------------------------------------------------
// A CBattery is a single battery with a label and a current charge level and loses charge every cycle.
class CBattery{
  
  public:
    // Creates a battery with the given label, fully charged.
    CBattery( const std::string& aName );
    // LoseCharge reduces the battery's charge level by 10% each cycle.
    void LoseCharge();
    // IsLow returns true if the battery is low on charge, ie below 80%.
    int IsLow();

  private:
    std::string mName;      // the battery's label, e.g. "Battery"
    double mCharge;          // current charge level, 0.0 to 1.0
};


//---CRobot--------------------------------------------------------------------
// A CRobot has a line sensor, a controller, and two drive motors. It offers
// operations described in terms of the whole robot rather than its parts.
class CRobot
{
  public:
    // Creates a robot with all of its parts ready to run.
    CRobot();

    // Update runs one cycle of the robot.
    void Update();

    // Report prints the state of the robot.
    void Report();

  private:
    CLineSensor mSensor;
    CController mController;
    CMotor mLeftMotor;
    CMotor mRightMotor;
    CBattery mBattery;
};

//---main----------------------------------------------------------------------
// Creates a robot, then runs it for a number of cycles, reporting it after
// each one.
int main()
{
  CRobot robot;

  for( int i = 0; i < NumCycles; ++i )
  {
    robot.Update();
    robot.Report();
  }

  return 0;
}

//---CLineSensor Implementation------------------------------------------------
CLineSensor::CLineSensor()
  : mCycle( 0 )
{
}
//---
int CLineSensor::Read()
{
  const int Track[NumCycles] = { 2, 1, -1, -2 };

  int reading = Track[ mCycle ];
  ++mCycle;

  return reading;
}

//---CController Implementation------------------------------------------------
CController::CController()
  : mLastError( 0.0 )
{
}
//---
double CController::ComputeSteering( int aError )
{
  double steering = 0.1 * aError + 0.05 * ( aError - mLastError );
  mLastError = aError;

  return steering;
}

//---CMotor Implementation-----------------------------------------------------
CMotor::CMotor( const std::string& aName )
  : mName( aName ),
    mSpeed( 0.0 )
{
}
//---
void CMotor::SetSpeed( double aSpeed )
{
  mSpeed = aSpeed;
}
//---
void CMotor::Report()
{
  std::cout << mName << " motor " << mSpeed;
}


//---CBattery Implementation-----------------------------------------------------
CBattery::CBattery( const std::string& aName ){
  mName = aName;
  mCharge = 1.0; // Fully charged
}
//---
void CBattery::LoseCharge(){
  mCharge -= 0.1; // Reduce charge by 10%
  if(mCharge < 0.0){
    mCharge = 0.0; // Ensure charge doesn't go below 0, not necessary for assignment but may be needed for A5.
  }
}
//---
int CBattery::IsLow()
{
  int Result;
  if (mCharge < 0.8)
  {
    Result = 1;
  }
  else
  {
    Result = 0;
  }
  return Result;
}
//---CRobot Implementation-----------------------------------------------------
CRobot::CRobot()
  : mLeftMotor( "Left" ),
    mRightMotor( "Right" ),
    mBattery( "Battery" )
{
}
//---
void CRobot::Update()
{
  mBattery.LoseCharge(); // Reduce battery charge each cycle
  int error = mSensor.Read();
  double steering = mController.ComputeSteering( error );
  double speed = BaseSpeed;

  if(mBattery.IsLow()){ 
    speed = BaseSpeed * 0.5; // Reduce speed by 50% if battery is low, changing it from 0.5 to 0.25
  }
  mLeftMotor.SetSpeed(speed + steering );
  mRightMotor.SetSpeed(speed - steering );
}
//---
void CRobot::Report()
{
  mLeftMotor.Report();
  std::cout << ", ";
  mRightMotor.Report();
  std::cout << std::endl;
}
