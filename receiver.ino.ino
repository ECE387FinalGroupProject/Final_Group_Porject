
int trigPin=10;
int echoPin=13;
int leftSensor = 22;
int rightSensor = 26;
int leftread = 0;
int rightread = 0;
int ledLeft = 6; 
int ledRight = 7;
//int ledFront = 4;
int remoteB = 3;
int ultraB = 4;
int irB= 5;
int remote=0,ultra=0,ir=0;
//Variables
bool started= false;//True: Message is strated
bool ended  = false;//True: Message is finished 
char incomingByte ; //Variable to store the incoming byte
char msg[3];    //Message - array from 0 to 2 (3 values - PWM - e.g. 240)
byte index;     //Index of array

void setup() {

  //Start the serial communication
  Serial.begin(9600); //Baud rate must be the same as is on xBee module
          pinMode(ledLeft, OUTPUT);
          pinMode(ledRight, OUTPUT);
 //     pinMode(ledFront, OUTPUT);
          pinMode(trigPin, OUTPUT);
          pinMode(echoPin, INPUT);
          pinMode(remoteB, INPUT);
          pinMode(ultraB,INPUT);
          pinMode(irB,INPUT);
          pinMode(leftSensor,INPUT);
          pinMode(rightSensor,INPUT);
 remote=digitalRead(remoteB);
 ultra=digitalRead(ultraB);
 ir=digitalRead(irB);
   Serial.print("b");
 while (ir==0&&ultra==0&&remote==0)
  {
     Serial.print("a");
  remote=digitalRead(remoteB);
  ultra=digitalRead(ultraB);
  ir=digitalRead(irB);
    }
   Serial.print(remote);
     Serial.print(ultra);
       Serial.print(ir);
}

void loop() {
 
  if (remote==1)
  {
   // Serial.println("remote control mode");
  while (Serial.available()>0){
    //Read the incoming byte
    incomingByte = Serial.read();
    //Start the message when the '<' symbol is received

    if(incomingByte == '<')
    {
     started = true;
     index = 0;
     msg[index] = '\0'; // Throw away any incomplete packet
   }
   //End the message when the '>' symbol is received
   else if(incomingByte == '>')
   {
     ended = true;
     break; // Done reading - exit from while loop!
   }
   //Read the message!
   else
   {
     if(index < 4) // Make sure there is room
     {
       msg[index] = incomingByte; // Add char to array
       index++;
       msg[index] = '\0'; // Add NULL to end
     }
   }
 }
 
 if(started && ended)
 {
   int value = atoi(msg);
     Serial.println(value); //Only for debugging
   if (value == 100)
   {
  //N     digitalWrite(ledFront, LOW);
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, LOW);
    }   
       if (value == 150)
   {
    //digitalWrite(ledFront, LOW);
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, HIGH);
    } 
       if (value == 200)
   {
//    digitalWrite(ledFront, HIGH);
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH);
    }  
    delay(100);
//    digitalWrite(ledFront, LOW);
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW); 
   
   index = 0;
   msg[index] = '\0';
   started = false;
   ended = false;
 }
  }
  if (ultra==1)
  {
    Serial.println("ultrasonic mode");
      float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance >= 15 && distance <= 30){
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
    delay(2000);
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH );
    delay(2000);
    }
  else if (distance <= 15 && distance >= 2){
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, LOW);
    delay(1000);
    
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, LOW);
    delay(3000);

    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH);
    delay(5000);

    digitalWrite(ledLeft, LOW);
    digitalWrite(ledRight, HIGH);
    delay(3000);

    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH);
    delay(5000);

    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, LOW);
    delay(3000);

    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH);
    delay(5000);
  }
  else {
    Serial.print("Distance = ");
    Serial.println("Out of range");
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH);
  }
  delay(3000);
    }
if (ir==1)
   {
    Serial.println("ir mode");
  leftread=digitalRead(leftSensor);
  Serial.println(leftread);
  rightread=digitalRead(rightSensor);
  Serial.println(rightread);
  if(leftread==1&&rightread==0){
    digitalWrite(ledLeft,LOW);
    digitalWrite(ledRight,HIGH);
  }
  if(leftread==0&&rightread==1){
     digitalWrite(ledLeft,HIGH);
     digitalWrite(ledRight,LOW);
  }
  if(leftread==0&&rightread==0){
     digitalWrite(ledLeft,HIGH);
     digitalWrite(ledRight,HIGH);
  }
  if(leftread==1&&rightread==1){
     digitalWrite(ledLeft,LOW);
     digitalWrite(ledRight,LOW);
  }
    }
}
  

