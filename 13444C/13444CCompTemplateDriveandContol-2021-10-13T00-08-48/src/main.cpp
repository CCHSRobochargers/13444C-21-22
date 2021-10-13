/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    12, 13
// Controller1          controller
// MotorGroup6          motor_group   6, 7
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// For autonomous selections
#define LINE_HEIGHT 40 // Character (line) height (pixels)

// Names for our autonomous routines
enum autoProg { none, auto1, auto2, auto3, autoOK };

const char *autoLabels[autoOK + 1] = {"NONE", "Auto1", "Auto2", "Auto3", "OK"};

// Which autonomous was selected (defaults to "none")
int autoSelect = 0;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  int fingerX;
  int fingerY;
  int selLine;

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Print the autonomous routine labels
  Brain.Screen.setFont(monoL);
  Brain.Screen.clearScreen();
  // Brain.Screen.setPenColor(white);
  for (int j = 0; j <= autoOK; j++) {
    Brain.Screen.setCursor(j+2, 5);
    Brain.Screen.print(autoLabels[j]);
  }

  // Look for finger presses
  while (true) {
    if (Brain.Screen.pressing()) {
      fingerX = Brain.Screen.xPosition();
      fingerY = Brain.Screen.yPosition();

      selLine =  fingerY / LINE_HEIGHT;
      Brain.Screen.setCursor(8, 1);
      Brain.Screen.print(autoSelect);

      // Press "OK" to accept
      if (selLine == autoOK) {
        break;
      }

      if (selLine < autoOK) {
        autoSelect = selLine;
      }
    }
    wait(20, msec);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  if (autoSelect == auto1) {
    MotorGroup6.spinToPosition(-200, degrees);
    Drivetrain.driveFor(forward, 21, inches);
    MotorGroup6.spinToPosition(-1000, degrees);
    Drivetrain.driveFor(reverse, 15, inches);
    MotorGroup6.spinToPosition(-1350, degrees);
  }

  // if (autoSelect == auto2) {
  //   MotorGroup6.spinToPosition(1350, degrees);
  //   Drivetrain.driveFor(forward, 15, inches);
  //   MotorGroup6.spinToPosition(1000, degrees);
  //   Drivetrain.driveFor(forward, 14, inches);
  //   MotorGroup6.spinToPosition(750, degrees);
  //   Drivetrain.driveFor(forward, 10, inches);
  // }
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
