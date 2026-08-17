# A5. Robot Controller

A robot controller that runs a set of subsystems. On each cycle the controller
runs every subsystem and reports its state. Designed so that further subsystems
can be added without modifying existing code.

## Layout

One class per file, flat. Declarations live in the `.h`, implementations in the
matching `.cpp`.

```
A5.RobotController/
├── main.cpp              Creates the controller and its subsystems, runs the cycles
├── CSubsystem.h/.cpp     Abstract base class: the interface every subsystem implements
├── CRobotController.h/.cpp   Holds the subsystems and drives them one cycle at a time
├── CDriveMotor.h/.cpp    Subsystem: actuator, holds its own speed state
├── CLineDetector.h/.cpp  Subsystem: sensor, holds its own line reading state
└── <third subsystem>     IN PROGRESS - kind not yet decided
```

## Responsibilities

**`CSubsystem`** defines the contract, and nothing else. It declares the pure
virtual per-cycle operation that every subsystem must implement, and holds only
the state common to all subsystems. It knows nothing about any particular
subsystem, so adding a new one never requires editing it.

**`CRobotController`** holds a collection of subsystems and runs them. It works
entirely through `CSubsystem`'s interface, so it never needs to know which
concrete kinds exist.

**The subsystems** each own their internal state and are responsible for
advancing and reporting it. They do not know about the controller or about each
other.

**`main.cpp`** wires the objects together and starts the run. No substantial
logic lives here.

## Interaction

`main` creates the subsystems and gives them to the controller. Each cycle, the
controller asks every subsystem to run and report, through the common interface.
Communication is one-way: the controller calls into the subsystems, never the
reverse.

## Status

- `CSubsystem`, `CRobotController`, `CDriveMotor`, `CLineDetector` — files
  created, not yet written.
- Third subsystem — **in progress**, kind to be confirmed by the group.
- Test code — not yet placed.

## Building

```bash
g++ -std=c++17 -Wall -Wextra *.cpp -o robot_controller && ./robot_controller
```
