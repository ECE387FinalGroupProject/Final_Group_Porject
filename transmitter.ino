

const int potPin = A0; //Pot at Arduino A0 pin 
//Variables:
int value ; //Value from pot
int front= 3;
int left=4;
int right=2;
int f=0,l=0,r=0;
int f1=0,f2=0;
int r1=0,r2=0;
int l1=0,l2=0;
void setup() {

  //Start the serial communication
  Serial.begin(9600); //Baud rate must be the same as is on xBee module
 pinMode(front,INPUT);
  pinMode(right,INPUT);
   pinMode(left,INPUT);
}

void loop() {
//debounce for 3 buttom
   f1=digitalRead(front);
   delay(50);
   f2=digitalRead(front);
   if (f1==f2)
   {
    f=f1;
    }
    else
    {
      f=0;
      }
     
   r1=digitalRead(right);
   delay(50);
   r2=digitalRead(right);
      if (r1==r2)
   {
    r=r1;
    }
    else
    {
      r=0;
      }
  l1=digitalRead(left);
  delay(50);
  l2=digitalRead(left);
  if (l1==l2)
  {
    l=l1;
    }
    else
    {
    l=0;
    }
 //send signal move forward has the most piority   
    if (l==1)
   {
    value = 100;
    }
    if (r==1)
    {
      value = 150;
      }
     if (f==1)
     {
      value=200;
      }
 
  //Send the message:
  Serial.print('<');  //Starting symbol
  Serial.print(value);//Value from 0 to 255
  Serial.println('>');//Ending symbol
value=0;

}
  
