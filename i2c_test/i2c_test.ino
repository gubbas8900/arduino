#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 0x04
int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int blink3 = 0;
int blink4 = 0;
int servo1 = 0;
int servo2 = 0;
int servo3 = 0;
int results = 0;
int dataReceived = 0;
int v[9];
int led3State = LOW;
int led4State = LOW;
long previousMillis = 0;
long interval = 1000;
Servo ser1;  // servo control object
Servo ser2;
Servo ser3;

void setup() {
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    ser1.attach(9);
    ser2.attach(8);
    ser3.attach(7);
    Serial.begin(9600);         // start serial for output
    // initialize i2c as slave
    Wire.begin(SLAVE_ADDRESS);

    // define callbacks for i2c communication
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);

    post();

    Serial.println("Ready!");
}

void loop() {
  if (dataReceived == 1) {
    loadVars();
    setLeds();
    setServos();
  }
    blinkLed();
    delay(500);
}

// callback for received data
void receiveData(int byteCount){

  Serial.print("Received bytes: ");
  Serial.println(byteCount);
  dataReceived = 1;

  int x = 0;
  while(Wire.available() > 0) {
      v[x] = Wire.read();
      Serial.println(v[x]);
      x++;
  }
}

void loadVars() {
  dataReceived = 0;
  led1 = v[0];
  led2 = v[1];
  led3 = v[2];
  led4 = v[3];
  blink3 = v[4];
  blink4 = v[5];
  servo1 = v[6];
  servo2 = v[7];
  servo3 = v[8];
  Serial.print("LED1: ");
  Serial.println(led1);
  Serial.print("LED2: ");
  Serial.println(led2);
  Serial.print("LED3: ");
  Serial.println(led3);
  Serial.print("LED4: ");
  Serial.println(led4);
  Serial.print("BLINK3: ");
  Serial.println(blink3);
  Serial.print("BLINK4: ");
  Serial.println(blink4);
  Serial.print("SERVO1: ");
  Serial.println(servo1);
  Serial.print("SERVO2: ");
  Serial.println(servo2);
  Serial.print("SERVO3: ");
  Serial.println(servo3);
}

void setLeds() {
        if (led1 == 1){
          digitalWrite(3, HIGH); // set the LED on
        }
          else{
            digitalWrite(3, LOW); // set the LED off
          }
        
        if (led2 == 1){
            digitalWrite(4, HIGH); // set the LED on
          }
          else{
            digitalWrite(4, LOW); // set the LED off
          }
        
        if (led3 == 1){
            digitalWrite(5, HIGH); // set the LED on
          }
          else{
            digitalWrite(5, LOW); // set the LED off
          }
        
        if (led4 == 1){
            digitalWrite(6, HIGH); // set the LED on
          }
          else{
            digitalWrite(6, LOW); // set the LED off
          }
}

void setServos() {
  if (ser1.read() != servo1) {
    ser1.attach(9);
    delay(500);
    ser1.write(servo1);
    delay(500);
    ser1.detach();
  }
  if (ser2.read() != servo2) {
    ser2.attach(8);
    delay(500);
    ser2.write(servo2);
    delay(500);
    ser2.detach();
  }
  if (ser3.read() != servo3) {
    ser3.attach(7);
    delay(500);
    ser3.write(servo3);
    delay(500);
    ser3.detach();
  }
}

void blinkLed() {
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;   

  if(led3 == 1 && blink3 == 1) {
    // if the LED is off turn it on and vice-versa:
    if (led3State == LOW)
      led3State = HIGH;
    else
      led3State = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(5, led3State);
   }
  if(led4 == 1 && blink4 == 1) {
    // if the LED is off turn it on and vice-versa:
    if (led4State == LOW)
      led4State = HIGH;
    else
      led4State = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(6, led4State);
   }
  }
}  

// callback for sending data
void sendData(){
    Wire.write(results);
}

void post() {
    ser1.attach(9);
    ser2.attach(8);
    ser3.attach(7);
    delay(500);
    ser1.write(90);
    ser2.write(90);
    ser3.write(90);
    delay(500);
    ser3.detach();
    ser2.detach();
    ser1.detach();

    digitalWrite(3, HIGH);
    delay(200);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    delay(200);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(200);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    delay(200);
    digitalWrite(6, LOW);
    
    led3 = 1;
    led4 = 1;
    blink3 = 1;
    blink4 = 1;
    int starttime = millis();
    int endtime = starttime;
    while ((endtime - starttime) <= 5000) {
      blinkLed();
      endtime = millis();
    }
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    
    ser1.attach(9);
    ser2.attach(8);
    ser3.attach(7);
    delay(500);
    int position = 0;
    
    for(position = 38; position < 151; position += 2)
  {
    ser2.write(position);  // Move to next position
    delay(20);               // Short pause to allow it to move
  }
    
    for(position = 22; position < 127; position += 2)
  {
    ser3.write(position);  // Move to next position
    delay(20);               // Short pause to allow it to move
  }
    
    for(position = 10; position < 176; position += 2)
  {
    ser1.write(position);  // Move to next position
    delay(20);               // Short pause to allow it to move
  }
    ser1.write(90);
    ser2.write(90);
    ser3.write(90);
    led3 = 0;
    led4 = 0;
    blink3 = 0;
    blink4 = 0;
}
