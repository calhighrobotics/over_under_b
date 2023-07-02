/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\debas                                            */
/*    Created:      Sun Jun 25 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftFront            motor         1               
// RightFront           motor         2               
// LeftBack             motor         3               
// RightBack            motor         4               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----



#include "vex.h"
#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <fstream>
//#include <auton.cpp>


using namespace vex;

// A global instannce of competition
competition Competition;


int check_next(int index, std::vector<uint8_t> values, int extent, int motorMax) {

  while (1) {
    bool pass = true;
    if (motorMax*2 < values.size()) {
      for (int i=0; i < motorMax; i++) {
        if (values[index+i] != values[index+motorMax]) {
          pass = false;
        }
      }
    }
    if (pass) {
      index += motorMax;
      extent += 1;
    } else {
      return extent;
    }
    

    /*if (index+23 < values.size() && values[index] == values[index+12] && values[index+1] == values[index+13] && values[index+2] == values[index+14] && values[index+3] == values[index+15] && values[index+4] == values[index+16] && values[index+5] == values[index+17] && values[index+6] == values[index+18] && values[index+7] == values[index+19] && values[index+8] == values[index+20]&& values[index+9] == values[index+21] && values[index+10] == values[index+22] && values[index+11] == values[index+23]) {
        index += 12;
        extent += 1;
    } else {
      return extent;
    }*/
  }
}


void pre_auton(void) {
  vexcodeInit();

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
//auton();
std::ifstream file("rerun.txt", std::ios::binary);
/*if (!file) {
  auton();
  return;
} */
//int size = 20000;
//uint8_t data[size];
std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
//Brain.SDcard.loadfile("rerun.txt", reinterpret_cast<uint8_t*>(data), size);

digital_out pneum = digital_out( Brain.ThreeWirePort.A);
for (int i=0; i < data.size(); i+=4) {
  RightFront.spin(vex::directionType::rev, data[i], vex::velocityUnits::pct);
  RightBack.spin(vex::directionType::rev, data[i+1], vex::velocityUnits::pct);
  LeftFront.spin(vex::directionType::rev, data[i+2],  vex::velocityUnits::pct);
  LeftBack.spin(vex::directionType::rev, data[i+3], vex::velocityUnits::pct);

  task::sleep(check_next(i, data, 1, 4)*10);
  i += 4*check_next(i, data, 1, 4) - 4;
}

file.close();

}


void initRerun(int rf, int rb, int lf, int lb) {
      uint8_t arr[12];
      arr[0] = rf;
      arr[1] = rb;
      arr[2] = lf;
      arr[3] = lb;
      Brain.SDcard.savefile("rerun.txt", arr, sizeof(arr));
}

void saveFrame(int rf, int rb, int lf, int lb) {
      //brain.SDcard.savefile(const char *name, uint8_t *buffer, uint32_t len);
      //"RFront.spin(vex::directionType::rev, rf, vex::velocityUnits::pct);"
      uint8_t arr[12];
      arr[0] = rf;
      arr[1] = rb;
      arr[2] = lf;
      arr[3] = lb;
      
      Brain.SDcard.appendfile("rerun.txt", arr, sizeof(arr));
      
      

}

void endRerun(void) {
    uint8_t data[20000];
    int written = Brain.SDcard.loadfile("rerun.txt", data, sizeof(data));
    Brain.Screen.clearScreen();
      if (written > 0) {
        Brain.Screen.setCursor( 2, 2 );
        Brain.Screen.print( "We wrote %d bytes to the SD Card", written );
      } else {
        Brain.Screen.setCursor( 2, 2 );
        Brain.Screen.print( "Well fuck, the write failed!");
      }
}

void usercontrol(void) {
  bool rerun = false;

  while (1) {
    int rf = Controller1.Axis3.value() - Controller1.Axis1.value() - Controller1.Axis4.value();
    int rb = Controller1.Axis3.value() - Controller1.Axis1.value() + Controller1.Axis4.value();
    int lf = Controller1.Axis3.value() + Controller1.Axis1.value() + Controller1.Axis4.value();
    int lb = Controller1.Axis3.value() + Controller1.Axis1.value() - Controller1.Axis4.value();
    
  

    //Drivetrain
    RightFront.spin(vex::directionType::rev, Controller1.Axis3.value() - Controller1.Axis1.value() - Controller1.Axis4.value(), vex::velocityUnits::pct);
    RightBack.spin(vex::directionType::rev, Controller1.Axis3.value() - Controller1.Axis1.value() + Controller1.Axis4.value(), vex::velocityUnits::pct);
    LeftFront.spin(vex::directionType::rev, Controller1.Axis3.value() + Controller1.Axis1.value() + Controller1.Axis4.value(),  vex::velocityUnits::pct);
    LeftBack.spin(vex::directionType::rev, Controller1.Axis3.value() + Controller1.Axis1.value() - Controller1.Axis4.value(), vex::velocityUnits::pct);


    //Rerun 
    if (Brain.SDcard.isInserted()) {
    if ((Controller1.ButtonUp.pressing() && !rerun)) {
      rerun = true;
      initRerun(rf, rb, lf, lb);
    } else if (rerun) {
      saveFrame(rf, rb, lf, lb);
    }else if (Controller1.ButtonDown.pressing()) {
      rerun = false;
      endRerun();
    }
  
  }
}
}




int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
  
}

