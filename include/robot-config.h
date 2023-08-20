using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftFront;
extern motor RightFront;
extern motor LeftBack;
extern motor RightBack;
extern controller Controller1;
extern motor LeftMid;
extern motor RightMid;
extern motor Catapult;
extern motor IntakeLeft;
extern motor IntakeRight;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );