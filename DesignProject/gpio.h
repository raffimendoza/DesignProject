#ifndef GPIO_H 
#define GPIO_H 

using namespace std; 

class gpio{ 
private: 
    int pin_num; //private variable that can only be accessed by a GPIO object 

public: 
    gpio(int a_pin_num); //constructor that creates the GPIO pin necessary 
    ~gpio(); //destructor  
    int get_val(); //getter that returns the value of the GPIO pin 
    void set_val(int val); //setter that set the value of the GPIO pin 
    void set_dir(string dir); //setter that sets the direction of the GPIO pin (in or out) 
}; 
#endif 