#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int number = 0;
int number1 = 0;
int number2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;
int state6 = 0;

void setup() {
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    Serial.begin(9600);         // start serial for output
    // initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);

    // define callbacks for i2c communication
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);

    Serial.println("Ready!");
}

void loop() {
    delay(100);
}

// callback for received data
void receiveData(int byteCount){

// Need to receive an array of LED1, LED2, LED3, LED4, LED5(blink3), LED6(blink4), SERVO1, SERVO2, SERVO3
// all at once and set accordingly...
//
// incomingByte[0] = Wire.read();
// incomingByte[1] = Wire.read();
// incomingByte[2] = Wire.read();
// incomingByte[3] = Wire.read();
// incomingByte[4] = Wire.read();
// incomingByte[5] = Wire.read();
// incomingByte[6] = Wire.read();
// incomingByte[7] = Wire.read();
// incomingByte[8] = Wire.read();
//
//
//
//
//
  while(Wire.available()) {
        number1 = Wire.read();
        number2 = Wire.read();
        Serial.print("data received: ");
        Serial.println(number1, number2);

        if (number == 3){

            if (state3 == 0){
                digitalWrite(3, HIGH); // set the LED on
                state3 = 1;
            }
            else{
                digitalWrite(3, LOW); // set the LED off
                state3 = 0;
            }
         }
        if (number == 4){

            if (state4 == 0){
                digitalWrite(4, HIGH); // set the LED on
                state4 = 1;
            }
            else{
                digitalWrite(4, LOW); // set the LED off
                state4 = 0;
            }
         }
        if (number == 5){

            if (state5 == 0){
                digitalWrite(5, HIGH); // set the LED on
                state5 = 1;
            }
            else{
                digitalWrite(5, LOW); // set the LED off
                state5 = 0;
            }
         }
        if (number == 6){

            if (state6 == 0){
                digitalWrite(6, HIGH); // set the LED on
                state6 = 1;
            }
            else{
                digitalWrite(6, LOW); // set the LED off
                state6 = 0;
            }
         }
        if (number > 3000){

            if (state6 == 0){
                digitalWrite(6, HIGH); // set the LED on
                state6 = 1;
                digitalWrite(5, HIGH); // set the LED on
                state5 = 1;
            }
            else{
                digitalWrite(6, LOW); // set the LED off
                state6 = 0;
                digitalWrite(5, LOW); // set the LED on
                state5 = 1;
            }
         }
     }
}

// callback for sending data
void sendData(){
    Wire.write(number);
}

