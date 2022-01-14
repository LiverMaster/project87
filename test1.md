#include <Servo.h>
Servo tgt1;
bool vo;
int count;
bool hit;
bool hit_old;


void setup() {

Serial.begin(9600);
pinMode(0,OUTPUT);
pinMode(4,INPUT);

digitalWrite(0,HIGH);
count = 0;
hit =0;
hit_old = 0;

tgt1.attach(5,500,2400);
tgt1.write(0);
delay(500);

for(int i=0; i<=90; i+=3)
  tgt1.write(i);
delay(300);
for(int j=90; j>=0; j-=3)
  tgt1.write(j);
delay(700);

for(int k=0; k<=78; k+=3)
  tgt1.write(k);
Serial.println("\n\n tgt1 initialized");
delay(1000);
}

void loop() {

vo=digitalRead(4);
//Serial.println(vo);

if(vo)
  {
  hit = 1;
  hit_old = hit;
  }
  else
  hit = 0;

if(hit_old == 1 && hit == 0)
  {
    count++;
    Serial.print(" ");
    Serial.print(count);
    Serial.println(" hit ");
    delay(300);    
    hit_old = 0;
    }
}