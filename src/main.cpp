#include <iostream> 
#include "gpio.h" //inlcude the  gpio header file to the main function to create objects from its gpio class 
#include "LCD.h"  //include the LCD header file to create objects from its LCD class 
#include <unistd.h> 
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <errno.h> 
#include <fstream>
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <ostream>
#include "MFRC522.h"
#include <chrono>
#include <ctime>

using namespace std; 

void delay(int ms){
#ifdef WIN32
  Sleep(ms);
#else
  usleep(ms*1000);
#endif
}


int main(){ 

LCD LCD_1(22, 17, 27, 24, 25, 5, 6, 13, 12, 16, 26); 

gpio green(0);  //GREEN LED
gpio red(1);  //RED LED



green.set_dir("out");
red.set_dir("out");
LCD_1.initialize(); 

LCD_1.print("Place Card");  
LCD_1.command(0XC0); //Shifts cursor to next line
LCD_1.print("For attendance");

usleep(700000);

LCD_1.command(0X01); //clears the screen
LCD_1.command(0X80); //brings cursor back to original position
LCD_1.print("LED blinks green");  
LCD_1.command(0XC0); //shifts cursor to next line
LCD_1.print("For authorized");
usleep(700000);
green.set_val(1); //prompts the GREEN LED to light up
usleep(100000); 
green.set_val(0); //prompts the GREEN LED to turn off

usleep(100000);

LCD_1.command(0X01);
LCD_1.command(0X80);
LCD_1.print("LED blinks red");  
LCD_1.command(0XC0);
LCD_1.print("For unauthorized"); 
usleep(700000);
red.set_val(1); //prompts the RED LED to light up
usleep(100000);
red.set_val(0); //prompts the RED LED to turn off

usleep(100000);

LCD_1.command(0X01); //clears the screen
LCD_1.command(0X80); //brings cursor back to original position
LCD_1.print("Please proceed");  


usleep(700000);

LCD_1.command(0X01); //clears the screen
LCD_1.command(0X80); //brings cursor back to original position
MFRC522 mfrc; //instantiates an object "mfrc" from the MFRC522 class, which allows us to setup the card reader
mfrc.PCD_Init(); 
cout << "Place Tag" << endl;
string authorized[5] = {"121846169","921635669","121175769","108175194192","3592123167"};  //array consisting of ID data of authorized cardholders
string names[5] = {"Solana Rowe","Christopher Smith", "Hykeem Carter", "Jane Doe", "Jourdan Riane"}; //array consisting of names of authorized cardholders
string DOB[5] = {"01/09/2000", "05/12/2001", "11/11/1999" , "04/04/2000" , "12/07/1999"}; //array consisting of date of birth of authorized cardholders
while(1){
	
	// Look for a card
    string userID = "";
    if(!mfrc.PICC_IsNewCardPresent())
      continue;

    if( !mfrc.PICC_ReadCardSerial())
      continue;
    //cout << "CARD DATA: ";
    for(byte i = 0; i < mfrc.uid.size; ++i){
      if(mfrc.uid.uidByte[i] < 0x10){
        //printf("%d",mfrc.uid.uidByte[i]);
        userID+=to_string(mfrc.uid.uidByte[i]);
      }
      else{
        
        //printf("%d", mfrc.uid.uidByte[i]);
        userID+=to_string(mfrc.uid.uidByte[i]);
      }
    
    }
	// Demo 4
    LCD_1.print(userID);
	LCD_1.command(0X01);
	LCD_1.command(0X80);
	usleep(1000000);
	
    time_t now = time(0);
	string currTime = ctime(&now); //Gets the time stamp of when a cardholder taps their card against the reader
	
    cout << endl;
    bool found = false;
    int userIndex = 0;
    for (int i = 0; i < 5; i++){
		if (userID == authorized[i]){
			found = true;
			userIndex = i;
			break;
		}
	}
	if (found == true){
		ofstream recordsFile("records.csv", ios_base::app); //Allows us to append data, rather than overwrite
		LCD_1.print("AUTHORIZED");
		usleep(700000);
		green.set_val(1);
		usleep(100000);
		green.set_val(0);
		LCD_1.command(0X01);
		LCD_1.command(0X80);
		recordsFile << authorized[userIndex] << ",";
		cout << "ID: " << authorized[userIndex] << endl;
		recordsFile << names[userIndex] << ",";
		cout << "AUTHORITY LEVEL: AUTHORIZED" << endl;
		cout << "NAME: " << names[userIndex] << endl;
		recordsFile << DOB[userIndex] << ",";
		cout << "DOB: " << DOB[userIndex] << endl;
		cout << "CURRENT TIME: " << currTime << endl;
		recordsFile << "AUTHORIZED" << ",";
		recordsFile << currTime;
		recordsFile << "\n";
		recordsFile.close(); //closes the file stream
	}else if (found == false){
		ofstream recordsFile("records.csv", ios_base::app); //Allows us to append data, rather than overwrite
		LCD_1.print("UNAUTHORIZED");
		usleep(700000);
		red.set_val(1);
		usleep(100000);
		red.set_val(0);
		LCD_1.command(0X01);
		LCD_1.command(0X80);
		cout << "ID: " << userID << endl;
		recordsFile << userID << ",";
		cout << "AUTHORITY LEVEL: UNAUTHORIZED" << endl;
		cout << "NAME: N/A" << endl;
		recordsFile << "N/A" << ",";
		cout << "DOB: N/A" << endl;
		cout << "CURRENT TIME: " << currTime << endl;
		recordsFile << "N/A" << ",";
		recordsFile << "UNAUTHORIZED" << ",";
		recordsFile << currTime;
		recordsFile << "\n";
		recordsFile.close(); //closes the file stream
	}
    cout << "***************************" << endl;
    cout << "Place Tag" << endl;
  }
return 0;
}  
