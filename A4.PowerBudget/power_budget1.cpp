// A device power budget v1
//
// This program reports how much power each device on a robot is drawing, and
// the total. Each device is turned on or off and set up, then its power draw is
// reported and added to the total.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//---CDevice-------------------------------------------------------------------
// A CDevice is a piece of equipment with a name that can be switched on or off.
class CDevice
{
  public:
    CDevice( const std::string& aName );

    void TurnOn();                            // switch the device on
    void TurnOff();                           // switch the device off
    bool IsOn();                              // whether the device is on
    const std::string& GetName();             // the device's label

  private:
    std::string mName;
    bool mIsOn;
};

//---CMotor--------------------------------------------------------------------
// A CMotor is a device whose power draw grows with its speed setting.
class CMotor : public CDevice
{
  public:
    CMotor( const std::string& aName );

    void SetSpeed( int aSpeed );              // set the motor's speed
    int PowerDraw();                          // power drawn, in watts

  private:
    int mSpeed;
};

//---CLed----------------------------------------------------------------------
// A CLed is a device whose power draw grows with its brightness setting.
class CLed : public CDevice
{
  public:
    CLed( const std::string& aName );

    void SetBrightness( int aBrightness );    // set the LED's brightness
    int PowerDraw();                          // power drawn, in watts

  private:
    int mBrightness;
};

//---main----------------------------------------------------------------------
// Sets up a motor and an LED, then prints each device's power draw and the
// running total.
int main()
{
  CMotor driveMotor( "DriveMotor" );
  driveMotor.TurnOn();
  driveMotor.SetSpeed( 30 );

  CLed statusLed( "StatusLed" );
  statusLed.SetBrightness( 50 );

  int total = 0;

  int motorDraw = driveMotor.PowerDraw();
  std::cout << driveMotor.GetName() << ": " << motorDraw << " W" << std::endl;
  total += motorDraw;

  int ledDraw = statusLed.PowerDraw();
  std::cout << statusLed.GetName() << ": " << ledDraw << " W" << std::endl;
  total += ledDraw;

  std::cout << "Total: " << total << " W" << std::endl;

  return 0;
}

//---CDevice Implementation----------------------------------------------------
CDevice::CDevice( const std::string& aName )
  : mName( aName ),
    mIsOn( false )
{
}
//---
void CDevice::TurnOn()
{
  mIsOn = true;
}
//---
void CDevice::TurnOff()
{
  mIsOn = false;
}
//---
bool CDevice::IsOn()
{
  return mIsOn;
}
//---
const std::string& CDevice::GetName()
{
  return mName;
}

//---CMotor Implementation-----------------------------------------------------
CMotor::CMotor( const std::string& aName )
  : CDevice( aName ),
    mSpeed( 0 )
{
}
//---
void CMotor::SetSpeed( int aSpeed )
{
  mSpeed = aSpeed;
}
//---
int CMotor::PowerDraw()
{
  return IsOn() ? mSpeed * 2 : 0;
}

//---CLed Implementation-------------------------------------------------------
CLed::CLed( const std::string& aName )
  : CDevice( aName ),
    mBrightness( 0 )
{
}
//---
void CLed::SetBrightness( int aBrightness )
{
  mBrightness = aBrightness;
}
//---
int CLed::PowerDraw()
{
  return IsOn() ? mBrightness / 10 : 0;
}
