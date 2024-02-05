#include "robot/wings.h"
#include "api.h"
#include "globals.h"


void Robot::Wings::check(){
    if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        wings = !wings;
    }
    if (wings) {
        wing.set_value(true);
        wing2.set_value(false);
        Robot::Wings::setState(true);
    }
    else {
        wing.set_value(false);
        wing2.set_value(true);
        Robot::Wings::setState(true);
    }
}

void Robot::Wings::setState(bool wingState) {
    state = wingState;
}

bool Robot::Wings::getState() {
    return state;
}