
#define echoPin 2 // Echo Pin
#define trigPin 3 // Trigger Pin
#define buzzPin 8 // Buzzer Pin

long duration, distance; // Duration used to calculate distance
char data = 0;            //Variable for storing received data
int messageSend = 0;
int alarm = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  pinMode(buzzPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;

    if (distance < 5 && distance > 0 ) {
      alarm = 1;
    } 

    if (alarm == 1) {
      if (messageSend == 0) {
        Serial.print(";ALARM;");
        messageSend = 1;
      }
      tone(8, 440, 250);
      delay(250);
      tone(8, 220, 250);
      delay(250);
    }

   if(Serial.available() > 0) {
      String income = Serial.readString();
      if (income == "STOP") {
        alarm = 0;
        messageSend = 0;
        delay(500);
      } else if (income == "OPEN") {
        messageSend = 0;
      }
   }
   
}
