#include "pitches.h"
#include <SoftwareSerial.h>
SoftwareSerial BluetoothSerial(2, 3); // RX, TX

#define motorIn1  6    //L298N IN1 D8
#define motorIn2  5    //L298N IN2 D7
#define motorIn3  8     //L298N IN3 D6
#define motorIn4  7     //L298N IN4 D5  

#define SensorRight   11    //右感測器輸入腳位 D11
#define SensorMiddle  12    //中感測器輸入腳位 D12
#define SensorLeft    13   //左感測器輸入腳位 D13

// notes in the melody:
int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_C4,
  NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4,
  NOTE_G4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_C4, 
  NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_F4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_C4, NOTE_C4,
  NOTE_D4, NOTE_E4, NOTE_F4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_C4, 
};

// note durations: 4 = quarter note, 8 = eighth note
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 2, 
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 2, 
};

int SR;    //右感測器
int SM;    //中感測器
int SL;    //左感測器 

const int pingPin = A1;
const int echoPin = A0;

const int DELAY = 1000;

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 0;    // variable to store the servo position 

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
 
  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  BluetoothSerial.begin(9600);

  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT); 

  myservo.attach(9);

  pinMode(10, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(19, OUTPUT);
  
}

void loop() // run over and over
{
  
  int Receive_Value;
  if (BluetoothSerial.available())
  { 
    Receive_Value = BluetoothSerial.read();
    Serial.println(Receive_Value);
    switch(Receive_Value)
    {     
        case 'F':
          while(1)
          {
            forward();
            Serial.println("forward");    
            if(BluetoothSerial.available())
            {
              Receive_Value = BluetoothSerial.read();
              Serial.println("Receive_Value");
              if(Receive_Value =='s')
                 stop();
              break;
            }
          }             
          break; 

        case 'L':
          while(1)
          {
            left();
            Serial.println("left");    
            if(BluetoothSerial.available())
            {
              Receive_Value = BluetoothSerial.read();
              Serial.println("Receive_Value");
              if(Receive_Value =='s')
                 stop();
              break;
            }
          }             
          break; 

        case'S':
          stop();
          Serial.println("stop");
          break; 

        case 'R':
          while(1)
          {
            right();
            Serial.println("right");    
            if(BluetoothSerial.available())
            {
              Receive_Value = BluetoothSerial.read();
              Serial.println("Receive_Value");
              if(Receive_Value =='s')
                 stop();
              break;
            }
          }             
          break; 

         case 'B':
          while(1)
          {
            backward();
            Serial.println("backward");    
            if(BluetoothSerial.available())
            {
              Receive_Value = BluetoothSerial.read();
              Serial.println("Receive_Value");
              if(Receive_Value =='s')
                 stop();
              break;
            }
          }             
          break; 

        case'T':
          while(1)
          {
            tracking();
            Serial.println("tracking");    
            if(BluetoothSerial.available())
            {
              Receive_Value = BluetoothSerial.read();
              Serial.println("Receive_Value");
              if(Receive_Value =='s')
                 stop();
              break;
            }
          }
          break; 

        case 'O':
          while(1)
          {
            avoid_obstacle();
            Serial.println("obstacle");    
            if(BluetoothSerial.available())
            {
              Receive_Value = BluetoothSerial.read();
              Serial.println("Receive_Value");
              if(Receive_Value =='s')
                 stop();
              break;
            }
          }             
          break; 

        case'D':
          while(1)
          {
            avoid_down();
            Serial.println("avoid_down");    
            if(BluetoothSerial.available())
            {
              Receive_Value = BluetoothSerial.read();
              Serial.println("Receive_Value");
              if(Receive_Value =='s')
                 stop();
              break;
            }
          }
          
          default:  
          break; 
          
    }
  }
}

void stop()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
}

void right()
{
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);

  digitalWrite(19, HIGH);   
  delay(350);              
  digitalWrite(19, LOW);    
  delay(350);              
}

void forward()
{
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);

  digitalWrite(16, HIGH);   
  delay(350);              
  digitalWrite(16, LOW);    
  delay(350);              
}

void left()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
  
  digitalWrite(10, HIGH);   
  delay(350);              
  digitalWrite(10, LOW);    
  delay(350);              
}

void backward()
{
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);

  digitalWrite(16, HIGH);   
  delay(350);              
  digitalWrite(16, LOW);    
  delay(350);              
}

void sing()
{
  for (int thisNote = 0; thisNote < 46; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(4, melody[thisNote], noteDuration);    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);    
    noTone(4);
  }
} 

void tracking()
{
  
 SL = digitalRead(SensorLeft);
 SM = digitalRead(SensorMiddle);
 SR = digitalRead(SensorRight);
  
      if (SM == HIGH)//中感測器在黑色區域
      { 
        if (SL == LOW && SR == HIGH) // 左白右黑, 向右轉彎 
        {  
            Serial.print("right\n");  
            left();
        } 
        else if (SL == HIGH && SR == LOW  ) // 左黑右白, 向左轉彎 
        {  
            Serial.print("left \n");   
            right();
        }
        else  // 兩側均為黑色或白色, 直進
        { 
             Serial.print("forward\n");           
             forward();
        }      
      } 
      else // 中感測器在白色區域
      {  
        if (SL == LOW && SR == HIGH) // 左白右黑, 快速右轉 
        {  
          Serial.print("right\n");
          right();
        }
        else if (SL == HIGH && SR == LOW ) // 左黑右白, 快速左轉 
        {  
           Serial.print("left\n");
           left();  
        }
        else // 都是白色, 停止
        {    
           Serial.print("motorstop\n");
           stop();
        }
      }  
}

void avoid_down()
{
   SL = digitalRead(SensorLeft);
   SM = digitalRead(SensorMiddle);
   SR = digitalRead(SensorRight);
   if (SL == LOW && SM == LOW && SR == LOW )
      {        
         Serial.print("forward\n");           
         forward();
      } 
   else
      {  
        Serial.print("motorstop\n");
        stop();
      }
}

long ask_distance(int angle)
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  myservo.write(angle);
 
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);
  return cm;

}

void avoid_obstacle()
{
  if (ask_distance(90)<=30)
  {
    stop();
    if(ask_distance(45)<ask_distance(135))
    {
      right();
      delay(DELAY);
      Serial.print("right");
    }
    else
    {
      left();     
      delay(DELAY);
      Serial.print("left");     
    }
  }  
  else
  {
    forward();
    delay(DELAY);
    Serial.print("forword");
  }
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING, there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
