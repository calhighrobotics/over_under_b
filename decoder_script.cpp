#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string intToBool(int num) {
    if (num == 1) {return "true";}
    return "false";
}

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
    }
}

int main() {

    ifstream file("rerun.txt", ios::binary);

    if (!file.is_open()) {
        cerr << "wrong filename buster" << endl;
        return 1;
    }

    vector<uint8_t> data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());


    vector<int> values(data.begin(), data.end());

    fstream auton;
    auton.open("auton.txt", ios::out);
    //auton << "void autonomous(void) {\n\t";

    for (int i=0; i < values.size(); i+=8) {
        int rf = values[i];
        int rb = values[i+1];
        int lf = values[i+2];
        int lb = values[i+3];
        int rm = values[i+4];
        int lm = values[i+5];
        int cat = values[i+6];
        int in = values[i+7];
        auton << "rf" << to_string(rf);
        auton << "rb" << to_string(rb);
        auton << "lf" << to_string(lf);
        auton << "lb" << to_string(lb);
        auton << "rm" << to_string(rm);
        auton << "lm" << to_string(lm);
        auton << "ca" << to_string(cat);
        auton << "in" << to_string(in);

        //string intake_fwd = intToBool(values[i+4]);
        //string intake_rev = intToBool(values[i+5]);
        //string rollers_fwd = intToBool(values[i+6]);
        //string rollers_rev = intToBool(values[i+7]);
        //string flywheel = intToBool(values[i+8]);
        //string extension_rev = intToBool(values[i+9]);
        //string extension_fwd = intToBool(values[i+10]);
        //string pn = intToBool(values[i+11]);

        /*auton << "RFront.spin(vex::directionType::rev," << to_string(rf) << ", vex::velocityUnits::pct);\n\t";
        auton << "RBack.spin(vex::directionType::rev, " << to_string(rb) << ", vex::velocityUnits::pct);\n\t";
        auton << "LFront.spin(vex::directionType::rev, " << to_string(lf) << ",  vex::velocityUnits::pct);\n\t";
        auton << "LBack.spin(vex::directionType::rev, " << to_string(lb) << ", vex::velocityUnits::pct);\n\t";
        auton << "Catapult.spin(vex::directionType::fwd, " << to_string(cat) << ", vex::velocityUnits::pct);\n\t";
        auton << "IntakeLeft.spin(vex::directionType::rev, " << to_string(in) << ", vex::velocityUnits::pct);\n\t";
        auton << "IntakeRight.spin(vex::directionType::fwd, " << to_string(in) << ", vex::velocityUnits::pct);\n\t";*/
        //auton << "if(" << intake_fwd << "){\n\tIntake.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);\n\t}";
        //auton << " else if( " << intake_rev << "){\n\tIntake.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);\n\t} else{\n\tIntake.stop(vex::brakeType::brake);\n}\n\t";
        //auton << "if( " << rollers_fwd << "){\n\tRollers.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);\n\t}";
        //auton << " else if(" << rollers_rev << "){\n\tRollers.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);\n\t} else{\n\tRollers.stop(vex::brakeType::brake);\n}\n\t";
        //auton << "  if(" << flywheel << "){\n\tFlyWheel.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);\n\t} else{\n\tFlyWheel.stop(vex::brakeType::coast);\n}\n\t";
        //auton << "digital_out pneum = digital_out( Brain.ThreeWirePort.A);\n\tif(" << pn << ") {\n\tpneum.set( true );\n\tthis_thread::sleep_for(500);\n\tpneum.set( false );\n}\n\t";
        //auton << "if(" << extension_rev << "){\n\tExtension.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);\n\t}";
        //auton << "else if(" << extension_fwd << "){\n\tExtension.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);\n} else{\n\tExtension.stop(vex::brakeType::brake);\n}\n\t";
        //auton << "task::sleep(10);\n\t";
        //auton << "task::sleep(" << check_next(i, data, 1, 6)*10 << ");\n\t";
        //i+= 6*check_next(i, data, 1, 6) - 6;
    }

    //auton << "}";

    return 0;
}