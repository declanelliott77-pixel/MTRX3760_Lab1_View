// A clock model, extended with an alarm clock built by inheritance
//
// This program models a simple clock that keeps a time in minutes and can
// advance, report, and reset it. CAlarmClock is a CClock that additionally
// holds an alarm time and reports when it is ringing. main() creates one plain
// clock and one alarm clock, and runs the alarm clock until it rings.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//--Constants------------------------------------------------------------------
// An alarm time of NoAlarmSet means no alarm is set on this clock
const int NoAlarmSet = -1;

//---CClock--------------------------------------------------------------------
// A CClock keeps a time, measured in whole minutes, and can advance it one
// minute at a time, report it, and reset it to where it started.
class CClock
{
  public:
    // Creates a clock with the given name and starting time, in minutes
    // since midnight.
    CClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM.
    void Report();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
};

//---CAlarmClock---------------------------------------------------------------
// A CAlarmClock is a CClock that also holds an alarm time and knows whether it
// is ringing. Ticking, resetting and timekeeping are inherited unchanged; only
// the alarm behaviour is added here.
class CAlarmClock: public CClock
{
  public:
    // Creates an alarm clock with the given name and starting time, in minutes
    // since midnight, and with no alarm set.
    CAlarmClock( const std::string& aName, int aStartMinutes );

    // SetAlarm sets the alarm time, in minutes since midnight.
    void SetAlarm( int aAlarmTime );

    // CheckRinging returns 1 if the alarm is ringing, 0 otherwise.
    int CheckRinging();

    // Report prints the clock as a CClock does, then notes whether the alarm
    // is ringing.
    void Report();

  private:
    int mAlarmTime;             // the time the alarm is set for, or NoAlarmSet
};

//---main----------------------------------------------------------------------
// Creates one plain clock and one alarm clock. The plain clock is advanced a
// single minute; the alarm clock is advanced until it rings.
int main()
{
  CClock clock( "Kitchen", 419 );    // 419 minutes = 06:59
  clock.Tick();
  clock.Report();

  CAlarmClock alarmClock( "Bedroom", 415 );    // 415 minutes = 06:55
  alarmClock.SetAlarm( 420 );                  // 420 minutes = 07:00
  while ( !alarmClock.CheckRinging() )
  {
    alarmClock.Tick();
    alarmClock.Report();
  }

  return 0;
}

//---CClock Implementation-----------------------------------------------------
CClock::CClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes )
{
}
//---
void CClock::Tick()
{
  ++mCurrentMinutes;
}
//---
int CClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
void CClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
}

//---CAlarmClock Implementation------------------------------------------------
// The member initialiser list hands the name and starting time to CClock, which
// is the only code permitted to initialise them; mAlarmTime is ours to set
CAlarmClock::CAlarmClock( const std::string& aName, int aStartMinutes )
  : CClock( aName, aStartMinutes ),
    mAlarmTime( NoAlarmSet )
{
}
//---
void CAlarmClock::SetAlarm( int aAlarmTime )
{
  mAlarmTime = aAlarmTime;
}
//---
// CClock's members are private, so the current time is read through GetTime()
int CAlarmClock::CheckRinging()
{
  if ( mAlarmTime == GetTime() )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
//---
// The name and time belong to CClock, so CClock prints them; this function adds
// only the alarm line that CClock knows nothing about
void CAlarmClock::Report()
{
  CClock::Report();

  if ( CheckRinging() )
  {
    std::cout << "Alarm ringing!" << std::endl;
  }
}
