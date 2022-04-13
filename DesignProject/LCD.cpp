#include "LCD.h"  

#include "gpio.h" 

#include <iostream> 
#include <string> 
#include <unistd.h> //this library will allow us to place time delayes  

using namespace std;  
 LCD::LCD(int a_E, int a_RS, int a_RW, int a_D0, int a_D1, int a_D2, int a_D3, int a_D4, int a_D5, int a_D6, int a_D7){ 

    //Allocating the space for each pointer object 
    E = new gpio(a_E); 
    RS= new gpio(a_RS); 
    RW= new gpio(a_RW); 
    D0= new gpio(a_D0); 
    D1= new gpio(a_D1); 
    D2= new gpio(a_D2); 
    D3= new gpio(a_D3); 
    D4= new gpio(a_D4); 
    D5= new gpio(a_D5); 
    D6= new gpio(a_D6); 
    D7= new gpio(a_D7); 

    //Setting the direction for each gpio each object is pointing to 
    E->set_dir("out"); 
    RS->set_dir("out"); 
    RW->set_dir("out"); 
    D0->set_dir("out"); 
    D1->set_dir("out"); 
    D2->set_dir("out"); 
    D3->set_dir("out"); 
    D4->set_dir("out"); 
    D5->set_dir("out"); 
    D6->set_dir("out"); 
    D7->set_dir("out"); 
    //Setting the default value for each gpio each object is pointing to 
    E->set_val(0); 
    RS->set_val(0); 
    RW->set_val(0); 
    D0->set_val(0); 
    D1->set_val(0); 
    D2->set_val(0); 
    D3->set_val(0); 
    D4->set_val(0); 
    D5->set_val(0); 
    D6->set_val(0); 
    D7->set_val(0); 
} 

 

LCD::~LCD(){ 
    delete E; 
    delete RS; 
    delete RW; 
    delete D0; 
    delete D1; 
    delete D2; 
    delete D3; 
    delete D4; 
    delete D5; 
    delete D6; 
    delete D7; 
} 

 

void LCD::command(int command){ 
    //setting the values for each gpio the objects are pointing to 
    RS->set_val(0); 
    RW->set_val(0); 
    //setting a bitwise function for each gpio and then moving the bit to the leftmost place 
    D0->set_val(command & 1);  
    D1->set_val((command & 2) >> 1); 
    D2->set_val(command & 4) >> 2); 
    D3->set_val(command & 8) >> 3); 
    D4->set_val(command & 16) >> 4); 
    D5->set_val(command & 32) >> 5); 
    D6->set_val(command & 64) >> 6); 
    D7->set_val(command & 128) >> 7); 
    usleep(100); 
    E->set_val(1); //turning on enable 
    usleep(100); 
    E->set_val(0); //turning off enable 
    usleep(10000); //putting a delay so there is enough time for the next instructions to run. 
} 

 

void LCD::print(string str){ 
//in order to iterate through the string that has been passed and get the value for each character, to later pass that value to the corresponding gpio pin, we used a for loop 
    for(int i = 0; i < str.length(); i++){ 
        char l_char = str.at(i); 
        int n = (int)l_char; //casting the character into int 
        usleep(40000); 
        RS->set_val(1); //for  printing into the LCD screen, RS value has to be 1 
        RW->set_val(0); 
        //setting a bitwise function for each gpio and then moving the bit to the leftmost place 
        D0->set_val(n & 1);  
        D1->set_val((n & 2) >> 1); 
        D2->set_val(n & 4) >> 2); 
        D3->set_val(n & 8) >> 3); 
        D4->set_val(n & 16) >> 4); 
        D5->set_val(n & 32) >> 5); 
        D6->set_val(n & 64) >> 6); 
        D7->set_val(n & 128) >> 7); 
        usleep(10000); 
        E->set_val(1); //turning on enable 
        usleep(10000); 
        E->set_val(0); //turning off enable 
        usleep(10000); //putting a delay so there is enough time for the next instructions to run. 
    } 
} 

void LCD::initialize(){ //This functions is passing the commands to initialize the LCD screen 
    usleep(40000); 
    command(0x38); //Function set: 8 bits, 2 lines, and 5x8 font size 
    command(0x38); //Function set: 8 bits, 2 lines, and 5x8 font size 
    command(0x0F); //Display ON 
    command(0x01); //Clear the display 
    command(0x06); //Entry mode: cursor/blink moves to the right and DDRAM address is increased by  1, and no shift display 
} 