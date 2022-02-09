/*
  Dimmer

 Demonstrates the sending data from the computer to the Arduino board,
 in this case to control the amperage of a CCC charger. The data is sent
 in individual bytes, each of which ranges from 0 to 255.  Arduino
 reads these bytes and uses them to set the amperage of a CCC charger.

 The circuit:
 Transistor attached from digital pin 9 to ground.
 Serial connection to Processing, Max/MSP, or another serial application

 created 2006
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe and Scott Fitzgerald

  Modified again by Derek Sloan
  7/22/15

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Dimmer

 */

const int CCC = 9;      // the pin that the CCC is attached to
  String amperage;
  int ampNum = 0;
  int scan = 0;

void setup()
{
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the CCC as an output:
  pinMode(CCC, OUTPUT);
}

void loop() {
//  byte amperage; // orginal

  
  // check if data has been sent from the computer:
  if (Serial.available()) {
    // read the most recent byte (which will be from 0 to 255):
    amperage = Serial.readString();
    ampNum = amperage.toInt();

    Serial.print ("I received the string ");    //send the string
    Serial.println (amperage); //New line
    Serial.println (); //New line

    if (ampNum > 255){
      ampNum = 255;
      Serial.print("It was High, we lowered it to ");
      Serial.println (ampNum);
    }
    // set the amperage of the CCC:
    // analogWrite(CCC, ampNum);
  }
if (ampNum>=240) ampNum=0;
ampNum = ampNum + 20;
Serial.println (ampNum);
analogWrite(CCC, ampNum);
delay (5000);
}
