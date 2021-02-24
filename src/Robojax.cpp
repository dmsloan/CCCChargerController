 /*
 * This Arduin to measure DC Current using The 75mV Shunt up to 500A
 *  50A 75mV, 100A 75mV, 200A 75mV, 300A, 500A 
 * 
 * Watch Video instrution for this code: https://youtu.be/9jwCc7uPGoc
 * 
 * Full explanation of this code and wiring diagram is available at
 * my Arduino Course at Udemy.com here: http://robojax.com/L/?id=62
 * Written by Ahmad Shamshiri on May 10, 2020 at 04:18 in Ajax, Ontario, Canada
 * in Ajax, Ontario, Canada. www.robojax.com
 * 
 * Get this code and other Arduino codes from Robojax.com
Learn Arduino step by step in structured course with all material, wiring diagram and library
all in once place. Purchase My course on Udemy.com http://robojax.com/L/?id=62

If you found this tutorial helpful, please support me so I can continue creating 
content like this. You can support me on Patreon http://robojax.com/L/?id=63

or make donation using PayPal http://robojax.com/L/?id=64

 *  * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Arduino.h>    // Arduino Framework <> searches the libraries paths

const int inPin =A0;//can change
const float SHUNT_CURRENT =100.00;//A
const float SHUNT_VOLTAGE =75.0;// mV
const float CORRECTION_FACTOR = 2.00;

const int ITERATION = 50; //can change (see video)
const float VOLTAGE_REFERENCE = 1100.00;//1.1V
const int BIT_RESOLUTION =10;//and 12 for Due and MKR
const boolean DEBUG_ONCE = true;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Robojax 50A Current for Arduino");
  //for line below see https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference
  analogReference(INTERNAL);//1.1V internal reference
  //analogReadResolution(BIT_RESOLUTION);//only Arduino with Due and MKR
  delay(500);
}

/*
 * getCurrent()
 * @brief gets current
 * @param none

 * @return returns one of the values above
 * Written by Ahmad Shamshiri for robojax.com
 * on May 10, 2020 at 03:05 in Ajax, Ontario, Canada
 */
float getCurrent()
{
 //robojax.com 50A Shunt Current Measurement for Arduino

    float averageSensorValue =0;
    int sensorValue ;
    float voltage, current;

    for(int i=0; i< ITERATION; i++)
    {   
      sensorValue = analogRead(inPin);
      delay(5);
      if(sensorValue !=0 && sensorValue < 100)
      {
        voltage = (sensorValue +0.5) * (VOLTAGE_REFERENCE /  (pow(2,BIT_RESOLUTION)-1)); 
        current  = voltage * (SHUNT_CURRENT /SHUNT_VOLTAGE )  ;
        if(i !=0){
          averageSensorValue += current+CORRECTION_FACTOR;
        }
        delay(1);
      }else{
        i--;
      }
    }    
   //IGNORE_CURRENT_BELOW
    averageSensorValue /=(ITERATION-1);
    return   averageSensorValue;
}//getCurrent()

/*
 * printCurrent()
 * @brief prints  the current on serial monitor
 * @param none
 * @return none
 * Written by Ahmad Shamshiri for robojax.com
 * on May 08, 2020 at 02:45 in Ajax, Ontario, Canada
 */
void printCurrent()
{
   Serial.println("Current:");
   Serial.print(getCurrent(),2);
   Serial.println("A");
   Serial.println();
}//printCurrent()

/*
 * printDebug()
 * @brief prints  the full details of current measurement
 * @param none
 * @return none
 * Written by Ahmad Shamshiri for robojax.com
 * on May 08, 2020 at 02:45 in Ajax, Ontario, Canada
 */

void printDebug()
{
  //robojax.com 50A Shunt Current Measurement for Arduino
    Serial.print("Debug Details Measureing ");
    Serial.print(ITERATION);
    Serial.println(" Times");
    Serial.print("Reading from pin: 	");
    Serial.println(inPin); 
    
    Serial.print("Shunt Voltage: 		");
    Serial.print(SHUNT_VOLTAGE);Serial.println("mV"); 
    Serial.print("Shunt Current: 		");
    Serial.print(SHUNT_CURRENT);Serial.println("A"); 
    Serial.print("Voltage Reference: 	");
    Serial.print(VOLTAGE_REFERENCE);Serial.println("mV"); 
    Serial.print("Bits Resolution: 	");
    Serial.print(BIT_RESOLUTION);Serial.println(" bits"); 
    Serial.println();        
    Serial.println("Sensor	Voltage		Current");    
    int sensorValue ;
    float voltage, current;
    float averageCurrentValue=0;

    for(int i=0; i< ITERATION; i++)
    {   
      sensorValue = analogRead(inPin);
      delay(5);
      if(sensorValue !=0 && sensorValue < 100)
      {      
        Serial.print(sensorValue);
        voltage = (sensorValue +0.5) * (VOLTAGE_REFERENCE /  (pow(2,BIT_RESOLUTION)-1)); 
        Serial.print("	");Serial.print(voltage);  
        current    = voltage * (SHUNT_CURRENT /SHUNT_VOLTAGE )  ;
        if(i !=0) averageCurrentValue += current+CORRECTION_FACTOR;
        Serial.print("mV		");Serial.print(current);Serial.println("A");                    
        delay(100);
      }else{
        i--;
      }
    }    

    averageCurrentValue /=(ITERATION-1);
    Serial.print("Average Current: ");   
    Serial.print(averageCurrentValue);            
    Serial.println("A");  
    Serial.println();   
    while(DEBUG_ONCE);
}//printDebug

// the loop routine runs over and over again forever:
void loop() {
  //robojax.com 50A Shunt Current Measurement for Arduino
  //printDebug();
  printCurrent();
  //getCurrent();
  delay(500);
}
