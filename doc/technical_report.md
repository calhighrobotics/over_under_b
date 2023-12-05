---
title: 1516B Rerun Technical Report
author:
- Aswath Subramanian
- Jay Demonte
abstract: |
    In this technical report, we examine the creation and usage of the program that we have created to run an autonomous program in the 2023-2024 VEX VRC competition. We show the details regarding how the tool was implemented and how the tool executes. Rerun is essentially a function embedded in our greater codebase to provide control for the robot, which repeats a prerecorded path with the same movements, at an accuracy of a couple centimeter inaccuracy. This report will detail the implementation and usage of the program in a programming language-agnostic way, allowing for the tool to be implemented in any other language. The report should be informative and detail everything that the "rerun" prgram aims to do.
header-includes:
  - \usepackage{enumitem}
  - \setlistdepth{20}
  - \renewlist{enumerate}{enumerate}{20}
  - \usepackage{hyphenat}


---

# Aim
    
"Rerun", as the program function is affectionately called by VEX VRC team 1516B, is a program that
aims to replicate an action that is given as input to a VRC robot. 

## Description of the Robot

The robot, which the function is written for, has a drivetrain comprised of 6 VEX smart motors,
and contains 2 pneumatic pumps to extend the "wings", which are simply C channels that are meant
to physically push the primary game object of the VEX VRC 2023-2024 Over Under Game. The C channels
push the triballs, shaped like acorns, along with it, and can move approximately 2-5 triballs at a
time, in a straight line. Additionally, there is a smart motor assigned to each the intake abd the 
catapult, which at a high level allow us to pick up the triballs and store it inside the robot as 
well as shoot it out via a catapult/trebuchet design when necessary.

## Function Goals

The function, named "Rerun", essentially aims to replicate the actions of the robot described above,
at any given time interval. It should be able to record it to a file and then be able to play back 
the recording of the robot's movement exactly. Given that the robot is placed in the same location 
as the start of the original recording, with the same start conditions, the function should be able 
to playback a copy of the movement, exactly as recorded. There can be an inaccuracy amount of a few 
inches, but the tasks completed by the robot while recording(ex: Moving triballs) should also be 
completed by the robot running the playback of the recording. All of the motors and pneumatic pumps 
on the robot must be replicated, and do the same actions as in the recording during playback. Finally, 
the playback of this recording of action must be executed by the robot completely without any 
intervention from the driver of the robot.

# Implementation

As the VEX ecosystem by defualt provides a moderately closed off set of libraries, it has proven somewhat
difficult and time-intensive for us to implement the intended feature set of the Rerun program. 

# Usage

# Results

# Potential Improvements

# Impact


