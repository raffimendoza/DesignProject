#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <ostream>

void delay(int ms){
#ifdef WIN32
  Sleep(ms);
#else
  usleep(ms*1000);
#endif
}

#include "MFRC522.h"

int main(){
  MFRC522 mfrc;

  mfrc.PCD_Init();
  cout << "Place Tag" << endl;
  while(1){
    // Look for a card
    
    if(!mfrc.PICC_IsNewCardPresent())
      continue;

    if( !mfrc.PICC_ReadCardSerial())
      continue;
    //cout << "Place Tag" << endl;
    // Print UID
    cout << "CARD DATA: ";
    for(byte i = 0; i < mfrc.uid.size; ++i){
      if(mfrc.uid.uidByte[i] < 0x10){
        //printf(" 0");
        
        printf("%X",mfrc.uid.uidByte[i]);
      }
      else{
        //printf(" ");
        printf("%X", mfrc.uid.uidByte[i]);
      }
    
    }
    printf("\n");
    delay(1000);
    cout << "Place Tag" << endl;
  }
  return 0;
}
