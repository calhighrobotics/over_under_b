# Dual Control


This document details the experimental prospect of using a double controller system in the VEX 1516B

## Code
According to the VEX documentation, another controller can be connected to the existing one using a connection cable and defining a new controller object that the existing controller is the parent of.

According to VEX C++ documentation, that object is defined as the following:

```cpp
//IMPORTANT: Note that the "controllerType" is in reference to the type that the parameter holds. "id" is the only actual parameter.
vex::controller::controller(controllerType: id)

// ID can be equal to primary, partner
// Here is an example.

vex::controller::controller(controllerType partner)
// this line would be the constructor used to create the controller object of a partner controller.
```

For example, the parent controller(AKA the main controller), which should be used to control the drivetrain and the main functions of the robot, can be defined as the following:

```cpp
controller Controller1 = controller(primary);
```
The partner controller can be initialized into a different object using the following code:
```cpp
controller Controller2 = controller(partner);
```

To make the controller usable, the methods associated with the primary controller can be reused under the partner controller. This would allow for the second controller to execute actions as required.

Seperation of concerns(functions of the robot) and good programming contstructs would be required in order to make sure the two controllers do not conflict.
## Physical Setup
In order to run the robot with the dual controller setup, the lead controller would be connected to the subject controller, with a V5 [Smart Cable](https://www.vexrobotics.com/v5-smart-cables.html).

Once this is done, the main program would be run from the master controller, and the functions assigned should execute from upon clicking the appropriate buttons.

*This section has not been tested or proven and therefore should not be taken as complete truth.*

## Resources

(https://www.vexforum.com/t/v5-dual-controller-code-and-controllertype-question/60318/12)

(https://api.vexcode.cloud/v5/class/classvex_1_1controller?member=classvex_1_1controller_1abd3ffed4bd7e54f2fe5d736c96d91d78)