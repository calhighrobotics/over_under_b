#include "main.h"
#include <ostream>

#include "api.h"
#include "pros/apix.h"
#include "pros/serial.h"
/*
           ___
          |_|_|
          |_|_|              _____
          |_|_|     ____    |*_*_*|
 _______   _\__\___/ __ \____|_|_   _______
/ ____  |=|      \  <_+>  /      |=|  ____ \
~|    |\|=|======\\______//======|=|/|    |~
 |_   |    \      |      |      /    |    |
  \==-|     \     |1516B |     /     |----|~~/
  |   |      |    |      |    |      |____/~/
  |   |       \____\____/____/      /    / /
  |   |         {----------}       /____/ /
  |___|        /~~~~~~~~~~~~\     |_/~|_|/
   \_/        |/~~~~~||~~~~~\|     /__|\
   | |         |    ||||    |     (/|| \)
   | |        /     |  |     \       \\
   |_|        |     |  |     |
              |_____|  |_____|
              (_____)  (_____)
              |     |  |     |
              |     |  |     |
              |/~~~\|  |/~~~\|
              /|___|\  /|___|\
             <_______><_______>
*/


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(1, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void displayLocation() {
	while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // pri∟nt the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}

void displayHi() {
	while (true) {
	// std::vector<std::int32_t> currents = drive_.get_current_draws();// get the current position of the robot
    pros::lcd::print(0, "Motor velocity draw");
	pros::lcd::print(1, "motor 1 vel: %lf", LeftFront.get_actual_velocity());
	pros::lcd::print(2, "motor 2 vel: %lf", RightFront.get_actual_velocity());
	pros::lcd::print(3, "motor 3 vel: %lf", LeftMid.get_actual_velocity());
	pros::lcd::print(4, "motor 4 vel: %lf", RightMid.get_actual_velocity());
	pros::lcd::print(5, "motor 5 vel: %lf", LeftBack.get_actual_velocity());
	pros::lcd::print(6, "motor 6 vel: %lf", RightBack.get_actual_velocity()); // print the x position// print the heading
        pros::delay(10);
    }
}


void initialize() {
	pros::lcd::initialize();
	
	if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_IMU) {
		chassis.calibrate();

		chassis.setPose(0, 0, 90); // X: 0, Y: 0, Heading: 0
		// Setting an example start location for the robot so it is all relatativistic 
		pros::Task screenTask(displayLocation);
	}
	else {
		pros::Task screenTask(displayHi);
	}
	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */



void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.<asd></asd>
 */
void competition_initialize() {
	/*if (controller.get_digital(DIGITAL_RIGHT)) {
		
		controller.set_text(0, 0, "Auton 1");
		auton++;
		controller.clear_line(0);
		if (auton == 4) {
			controller.set_text(0, 0, "Auton 1");
			auton = 1;
			controller.clear_line(0);
		}
	}*/

}
	









/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	
	if(auton == 1){
		// Autonomous for Far side defensive zone.
		
		if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_IMU) {
			chassis.setPose(-32.862, -58.306, 90);
			chassis.moveTo(-0.979, -59.856, 8000);
			chassis.moveTo(37.281, -58.478, 8000);
			chassis.moveTo(47.449, -52.791, 5000);
			chassis.moveTo(54.859, -43.869, 5000);
			chassis.moveTo(59.168, -27.113, 5000);

		}
		else {
			drive_.move_velocity(150);
			pros::delay(5000);
			drive_.brake();
			drive_right.move_velocity(180);
			pros::delay(350);
			drive_.move_velocity(170);
			pros::delay(3000);
			
		}



		
	}
	if(auton == 2){
		// Autonomous for near side offensive zone.

		if (pros::c::registry_get_plugged_type(13) == pros::c::E_DEVICE_IMU) {
			chassis.setPose(37.281, -58.306, 35);
			chassis.moveTo(47.449, -52.791, 5000);
			chassis.moveTo(54.859, -43.869, 5000);
			chassis.moveTo(59.168, -27.113, 5000);
		}
		else {
			drive_.move_velocity(150);
			pros::delay(2000);
			drive_.brake();
			drive_right.move_velocity(180);
			pros::delay(550);
			drive_right.brake();
			drive_.move_velocity(170);
			pros::delay(3000);
		}
		
	}


		if(auton == 3){
		// Autonomous routine for the Skills challenge
			while (true) {
				Puncher.move(95);
			}

		}
		}







/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

    while (true) {
        Drivetrain::ArcadeDrive();
		


		if (controller.get_digital(DIGITAL_L2)) {
			Puncher.move(127);
		}
		else if (controller.get_digital(DIGITAL_R2)) {
			Puncher.move(-127);
		}
		else {
			Puncher.brake();
		}


		if (controller.get_digital(DIGITAL_L1)) {
			Intake.move(127);
		}
		else if (controller.get_digital(DIGITAL_R1)) {
			Intake.move(-127);
		}
		else {
			Intake.brake();
		}

		// Catapult controller, uses the X button holded down to push the elevation up.
		

		// Intake controller, moves the left and right intakes and stops them if nothing is pressed.
	

		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			wings = !wings;
		}
		if (wings) {
			wing.set_value(true);
			wing2.set_value(false);
		}
		else {
			wing.set_value(false);
			wing2.set_value(true);
		}

		// if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
		// 	if (subsystem == 1) {
		// 		// intake
		// 		controller.set_text(0, 0, "System : Intake");
		// 		pto_1.set_value(false);
		// 		pto_2.set_value(true);
		// 		controller.clear_line(0);
		// 	}
		// 	if (subsystem == 2) {
		// 		// Four Bar
				
		// 		controller.set_text(0, 0, "System : 4-bar");
		// 		pto_1.set_value(true);
		// 		pto_2.set_value(true);
		// 		controller.clear_line(0);
				
		// 	}
		// 	// if (subsystem == 3) {
		// 	// 	// Flywheel
		// 	// 	controller.clear_line(0);
		// 	// 	pto_1.set_value(true);
		// 	// 	pto_2.set_value(false);
		// 	// 	controller.print(1, 0, "System : Flywheel");
		// 	// }

		// 	subsystem = subsystem + 1;

		// 	// Checks if the toggler goes out of bounds.
		// 	if (subsystem == 3) {
		// 		subsystem = 1;
		// 	}

		// }


		
    


        pros::delay(2); // Small delay to reduce CPU usage
    }
	
	
}
