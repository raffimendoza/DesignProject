#include "gpio.h" //we include the header file to the cpp 
#include <fstream> //this library will allow us to open files 
#include <string> 

using namespace std; 

gpio::gpio(int a_pin_num){ 
    pin_num = a_pin_num; 
    ofstream pint_file ("/sys/class/gpio/export"); //open file export 
    pin_file << pin_num; //set the pin number for the GPIO we are going to use 
    pin_file.close(); //close the file 
} 

gpio::~gpio(){ 
    set_val(0); 
    set_dir("in"); 

    ofstream pint_file ("/sys/class/gpio/unexport"); //open file unexport 
    pin_file << pin_num; 
    pin_file.close(); 
} 
 

void gpio::set_dir(string dir){ 
    ofstream pint_file ("/sys/class/gpio/gpio" + to_string(pin_num) + "/direction"); //open file direction 
    pin_file << dir; //set the direction of the corresponding GPIO 
    pin_file.close(); //close the file 
} 

void gpio::set_val(int val){ 
    ofstream pint_file ("/sys/class/gpio/gpio" + to_string(pin_num) + "/value");//open file value 
    pin_file << to_string(val); //set the value of the corresponding GPIO (0 or 1) 
    pin_file.close(); //close the file 
} 

int gpio::get_val(){ 
    int val; 
    ifstream pint_file ("/sys/class/gpio/gpio" + to_string(pin_num) + "/value");//open file value 
    pin_file >> val; //assign the value of the GPIO to the variable int val 
    pin_file.close(); //close the file 
    return val; //return the value of the GPIO 
} 