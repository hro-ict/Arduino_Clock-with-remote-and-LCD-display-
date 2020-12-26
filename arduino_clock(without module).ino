#include <Wire.h>
#include <LiquidCrystal_I2C.h> // lcd display library
#include <IRremote.h> //remote library
int RECV_PIN = 10;// remote pin
#include <SPI.h>
#include <SD.h>




IRrecv irrecv(RECV_PIN);
decode_results results;
LiquidCrystal_I2C lcd(0x27, 16, 2);
//char *dagen[]= {"Maandag  ", "Dinsdag  ", "Woensdag ", "Donderdag", "Vrijdag   ", "Zaterdag ", "Zondag   "};

//de tijd begint om 12:00
int uur=12;
int minuut=00;
int seconden=00;

String text_sec, text_min, text_uur, dag;
int count_dag=1;

void setup() {
  Serial.begin(9600);
    lcd.init();
      irrecv.enableIRIn();

    

}

void loop() {
  

 //afstandsbediening toetsen
if (irrecv.decode(&results)){

 switch(results.value){
  case 0xFF629D: minuut+=1;break; //UP toets 
  case 0xFFA857:minuut-=1;break; //DOWN toets
  case 0xFFC23D: uur+=1;break;// RIGHT toets
  case 0xFF22DD:uur-=1;break;//LEFT toets
  case 0xFF02FD:seconden=0;break;// OK toets

  
  
  //////dagen
  case 0xFF6897: count_dag=1;break;//maandag
  case 0xFF9867: count_dag=2;break;//dinsdag
  case 0xFFB04F: count_dag=3;break;//Woensdag
  case 0xFF30CF: count_dag=4;break;//donderdag
  case 0xFF18E7: count_dag=5;break;//vrijdag
  case 0xFF7A85: count_dag=6;break; //zaterdag
  case 0xFF10EF: count_dag=7;break;//zondag
  
  
  
  }
  
  delay(50);
  irrecv.resume();
  
  }

switch(count_dag){
case 1: dag=dagen[0];break;
case 2: dag=dagen[1];break;
case 3: dag=dagen[2];break;
case 4: dag=dagen[3];break;
case 5: dag=dagen[4];break;
case 6: dag=dagen[5];break;
case 7: dag=dagen[6];break;
case 8: count_dag=1;break;
}


  
if (String(seconden).length()==1)
text_sec= "0"+String(seconden);
else
text_sec= String(seconden);
if (String(minuut).length()==1)
text_min= "0"+String(minuut);
else
text_min= String(minuut);
if (String(uur).length()==1)
text_uur= "0"+String(uur);
else
text_uur= String(uur);
lcd.backlight();
lcd.setCursor(0,0);
//Serial.println(text_uur+ ": "+ text_min+ ": "+ text_sec);
lcd.print(text_uur+ ":"+ text_min+ ":"+ text_sec+);
lcd.setCursor(3,1);
lcd.print(dag);
 

  if (minuut>59){
    uur+=1;
    minuut=0;
    seconden=1;
    }
  else if (seconden>59){
  minuut+=1;
  seconden=0;}
  else if (seconden<=59){
  seconden+=1;}

  if (uur>23){
    uur=0;
    count_dag+=1;
    
    }
  delay(1000);

}
