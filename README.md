# Access Control System using RFID tag and RDIF-RC522 Reader

run:
cd src

g++ MFRC522.cpp main.cpp LCD.cpp gpio.cpp -o main -std=c++11 -lbcm2835

sudo ./main
