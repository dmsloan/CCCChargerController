/*
  Demonstrates the sending data from the computer to the Arduino board,
 in this case to control the amperage of a CCC charger. The data is sent
 in individual bytes, each of which ranges from 0 to 255.  Arduino
 reads these bytes and uses them to set the amperage of a CCC charger.

 The circuit:
 Transistor base attached from digital pin 9,  to ground.
 Serial connection to PC

Modified again by Derek Sloan
7/27/15
 
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
    if (amperage.toInt() > 60){
      amperage = "60";
      Serial.print("It was High, we lowered it to ");
      Serial.println (amperage);
    }
    ampNum = amperage.toInt();
    ampNum = map(ampNum,0,60,0,255);

    Serial.print ("I received the request of ");    //send the string
    Serial.println (amperage); //New line
//    Serial.println (ampNum);
    Serial.println (); //New line

    // set the amperage of the CCC:
    // analogWrite(CCC, ampNum);
  }

//Serial.println (ampNum);
analogWrite(CCC, ampNum);
}
