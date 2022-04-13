#include <iostream> 
#include "gpio.h" //inlcude the  gpio header file to the main function to create objects from its gpio class 
#include "LCD.h"  //include the LCD header file to create objects from its LCD class 
#include <unistd.h> 
 
using namespace std; 

int main(){ 
LCD blink_1(22, 17, 27, 24, 25, 5, 6, 13, 12, 16,  26); 
blink_1.initialize(); 
blink_1.print("Hello World"); 
blink_1.command(0xC0); //This command will move the cursor to the bottom line 
blink_1.print("CSE398"); 
blink_1.command(0x80); //This command will move the cursor back to the top line 
blink_1.command(0x01); //clear the LCD screen command 
//while(1){} 
}  