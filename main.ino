// Electromagnet Levitation Device
int anaPin = 0;   // Arduino Analogic Pin 0 (hall sensor);
int digPin = 5;   // Arduino Digital  Pin 5 (resistor);
int subPin = 7;   // Arduino Digital  Pin 7 (microswitch);
int addPin = 8;   // Arduino Digital  Pin 8 (microswitch);
int echoPin = 10; // Arduino Digital  Pin 10 (echo distance sensor);
int trigPin = 9; // Arduino Digital  Pin 9 (trig distance sensor);
//
int     anaVal = 0;   // Analogic Read(Hall Sensor) Value;
boolean digVal = 255;   // Digital Write(Electromagnet) Value;

float duration, distance; // distance sensor

int levVal = 473;   // Levitation Point Value(497~507);
int dlyVal = 0.05;   // Delay Value Micro Seconds;
//---------------------------------------------------------|
//Setup
void setup()
{
   // Levitator initialization Begin; 
   Serial.begin(57600);
   Serial.println("Levitation Device");
   Serial.println("Starting...");
   // Digital Pins Work Mode Setup;
   pinMode(digPin, OUTPUT);
   pinMode(subPin, INPUT_PULLUP);
   pinMode(addPin, INPUT_PULLUP);
   pinMode(trigPin, OUTPUT);
   pinMode(echoPin, INPUT);
   // Levitator initialization End; 
   Serial.println("Started.");
}
//---------------------------------------------------------|
// Loop
void loop() 
{
   // Hall Sensor Read (Magnetic Field Intensity);
   anaVal = analogRead(anaPin);

   // Distance Sensor Code
   digitalWrite(trigPin, LOW);
   delayMicroseconds(0.5);
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(0.5);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   distance = (duration * 0.0343) / 2;
   Serial.print("Distance: ");
   Serial.println(distance);

   // Increase The Value Of Levitation Point;
   if (digitalRead(addPin) == LOW) 
   {
      levVal++;
      value_log();
      delay(0.05);
   }
   // Decrease The Value Of Levitation Point;
   if (digitalRead(subPin) == LOW) 
   {
      levVal--;
      value_log();
      delay(0.05);
   }
   // Check the Levitation Point;
   if (anaVal < levVal) 
   {
      digVal = LOW;
   }
   else // if (anaVal > levVal) 
   {
      digVal = HIGH;
   }
   //
   // Turn ON/OFF The Electromagnet;
   // With Base on Sensor Value and the Levitation Point;
   digitalWrite(digPin, digVal);
   delayMicroseconds(dlyVal);
}
//---------------------------------------------------------|
void value_log()
// Analogic/Digital/Levitation Values Print;
{
   // Show the Hall Sensor Value;
   Serial.print("Hall sensor reading (anaVal)=[");
   Serial.print(anaVal); 
   Serial.print("]-");
   // Show the Electromagnet state On=1/Off=0;
   Serial.print("digVal=[");
   Serial.print(digVal);
   Serial.print("]-");
   // Show the Levitation Point Value;
   Serial.print("Levitation point (levVal)=[");
   Serial.print(levVal);
   Serial.println("];");
}
