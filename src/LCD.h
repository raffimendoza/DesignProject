#ifndef LCD_H 
#define LCD_H 
#include <string> 
#include "gpio.h" //the gpio header file needs to be addes in order to create gpio objects and access to gpio functions. 
#include <iostream>
class LCD{ 
    private: 
        gpio * E, * RS, * RW, * D0, * D1, * D2, * D3, * D4, * D5, * D6, * D7; //private gpio pointer objects 

    public: 
        LCD(int a_E, int a_RS, int a_RW, int a_D0, int a_D1, int a_D2, int a_D3, int a_D4, int a_D5, int a_D6, int a_D7); //constructor with int parameters 
        ~LCD(); //destructor 
        
        void command(int command); //command function with a int parameter 
        void print(string str); //print function with string parameter 
        void initialize(); //initialize function with no parameters 
}; 
#endif 
