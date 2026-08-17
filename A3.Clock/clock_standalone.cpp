// A clock model
//
// This program models a simple clock that keeps a time in minutes and can
// advance, report, and reset it. main() creates one plain clock and steps it
// forward by a minute.
//
// Edit this file directly to build the version asked for in the handout.
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
// The standalone alarm clock without inheritance: it keeps its own time and its
// own alarm setting.
class CAlarmClock
{
  public:
    // Creates an alarm clock with the given name and starting time, in
    // minutes since midnight.
    CAlarmClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM, and notes
    // whether the alarm is ringing.
    void Report();

    // SetAlarm sets the alarm time, in minutes since midnight.
    void SetAlarm( int aAlarmTime );

    // CheckRinging returns 1 if the alarm is ringing, 0 otherwise.
    int CheckRinging();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
    int mAlarmTime;             // the time the alarm is set to, in minutes since midnight
};

//---main----------------------------------------------------------------------
// Creates one plain clock, starts it at 06:59, advances it one minute, and
// reports it.
int main()
{
  CClock clock( "Kitchen", 419 );    // 419 minutes = 06:59
  clock.Tick();
  clock.Report();

  // Create an alarm clock alongside the plain clock, set its alarm, and advance
  // it a minute at a time until it rings
  CAlarmClock alarmClock( "Bedroom", 415  );    // 415 minutes = 06:55
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
CAlarmClock::CAlarmClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes ),
    mAlarmTime( NoAlarmSet )
{
}
//---
void CAlarmClock::Tick()
{
  ++mCurrentMinutes;
}
//---
int CAlarmClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CAlarmClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
// Report renders the whole of the alarm clock's state, ringing included, so
// that callers never have to assemble it themselves
void CAlarmClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes;

  if ( CheckRinging() )
  {
    std::cout << " - Alarm ringing!";
  }

  std::cout << std::endl;
}
//---
void CAlarmClock::SetAlarm( int aAlarmTime )
{
  mAlarmTime = aAlarmTime;
}
//---
int CAlarmClock::CheckRinging()
{
  if ( mAlarmTime == mCurrentMinutes )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
