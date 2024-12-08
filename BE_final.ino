#include<SoftwareSerial.h>
SoftwareSerial bt(4,3); /* (Rx,Tx) */
// Green and black thread for thumb 
int FLEX_PIN1 = A0;
int flexADC1 = 0;
int sensorMin1 = 390;
int sensorMax1 = 610;
// Red and brown thread for the index finger //
int FLEX_PIN2 = A1;
int flexADC2 = 0;
int sensorMin2 = 245;
int sensorMax2 = 565;
// Red and green string for the middle //
int FLEX_PIN3 = A2;
int flexADC3 = 0;
int sensorMin3 = 310;
int sensorMax3 = 610;
// Yellow and brown thread for the ring finger //
int FLEX_PIN4 = A3;
int flexADC4 = 0;
int sensorMin4 = 330;
int sensorMax4 = 600;
// Green and blue thread for the pinky //
int FLEX_PIN5 = A4;
int flexADC5 = 0;
int sensorMin5 = 325;
int sensorMax5 = 605;
int xpin = A7;
int xadc = 0;
int ypin = A6;
int yadc = 0;
int count = 0;
String str = "";
String lastletter = "";
String letter = "";

bool sent = false;
String pyString = "";  // 保存從 Python 接收的字串
bool stringComplete = false;

bool compare(int a, int b, int c){
  if ( b+c >= a && a >= b -c) return true;
  else return false;
}

void setup() {
  Serial.begin(1200);
  bt.begin(9600);
  pyString.reserve(200);  // 預留緩衝區大小
}

void loop() {

  float flexADC1 = analogRead(FLEX_PIN1);
  flexADC1 = constrain(flexADC1,sensorMin1, sensorMax1);
  float angle1= 100 - map(flexADC1, sensorMin1, sensorMax1, 0, 100);
  float flexADC2 = analogRead(FLEX_PIN2);
  flexADC2 = constrain(flexADC2,sensorMin2, sensorMax2);
  float angle2= 100 - map(flexADC2, sensorMin2, sensorMax2, 0, 100);
  float flexADC3 = analogRead(FLEX_PIN3);
  flexADC3 = constrain(flexADC3,sensorMin3, sensorMax3);
  float angle3= 100 - map(flexADC3, sensorMin3, sensorMax3, 0, 100);
  float flexADC4 = analogRead(FLEX_PIN4);
  flexADC4 = constrain(flexADC4,sensorMin4, sensorMax4);
  float angle4= 100 - map(flexADC4, sensorMin4, sensorMax4, 0, 100);
  float flexADC5 = analogRead(FLEX_PIN5);
  flexADC5 = constrain(flexADC5,sensorMin5, sensorMax5);
  float angle5= 100 - map(flexADC5, sensorMin5, sensorMax5, 0, 100);
  xadc = analogRead(xpin);
  yadc = analogRead(ypin);
  bool horizontal (((xadc>=330)&&(xadc<=400))&&((yadc>=270)&&(yadc<=300)));
  bool vertical = (((xadc>=270)&&(xadc<=300))&&((yadc>=340)&&(yadc<=400)));
  bool equilibrium =(((xadc>=330)&&(xadc<=400))&&((yadc>=330)&&(yadc<=400)));

  if(compare(angle2,5,10)  && compare(angle4,90,20) && compare(angle5,90,20)){
    if( 45 <= angle1 <= 55 && 25 >= angle3 && angle3 >= 10){
        letter = "r";
    }else if (angle3 < 10){
      if ( angle1 <= 25 ){
        letter = "k";
      } else if (angle1 >= 55){
        letter = "u";
      } else{
        if(vertical){
          letter = "v";
        }
      }
    }
  }

  if(angle2 > 75 && angle3 > 60  && angle4 > 75 && angle5 > 75){
    if(angle1 < 30){
      letter = "a"; 
    }else if(vertical){
      if ( angle1 > 70 ){
        letter = "s";
      }else if ( angle1 >30 ){
        letter = "t";
      }
    }

  }else if (compare(angle3,65,10) && compare(angle4,65,13) && compare(angle5,65,13) && angle1>55 && angle2>60 && angle2<75 && vertical){
      letter = "e";
  }
  
  if(compare(flexADC1,460,40) && compare(flexADC2,540,40) && compare(flexADC3,600,40) && compare(flexADC4,580,40) && compare(flexADC5,600,40)){
    letter = "b";
  }

  if(compare(flexADC1,565,40) && compare(flexADC2,440,40) && compare(flexADC3,510,40) && compare(flexADC4,510,40) && compare(flexADC5,540,40) && !vertical){
    letter = "c";
  }

  if(compare(flexADC1,475,40) && compare(flexADC2,550,40) && compare(flexADC3,452,40) && compare(flexADC4,465,40) && compare(flexADC5,465,40)){
    letter = "d";
  }
  
  if(compare(flexADC1,515,40) && compare(flexADC2,350,40) && compare(flexADC3,605,40) && compare(flexADC4,590,40) && compare(flexADC5,605,40)){
    letter = "f";
  }

  if(compare(flexADC1,550,40) && compare(flexADC2,557,40) && compare(flexADC3,355,40) && compare(flexADC4,365,40) && compare(flexADC5,365,40) && horizontal){
    letter = "g";
  }
  
  if(compare(angle1,40,12) && compare(angle2,0,10) && compare(angle3,0,10) && compare(angle4,80,15) && compare(angle5,85,15) && horizontal){
    letter = "h";
  }

  if(compare(angle1,70,15) && compare(angle2,85,15) && compare(angle3,75,20) && compare(angle4,90,10) && compare(angle5,5,10) && vertical){
    letter = "i";
  }

  if(compare(angle1,70,15) && compare(angle2,85,15) && compare(angle3,75,20) && compare(angle4,90,10) && compare(angle5,5,10) && !vertical){
    letter = "j";
  }
  
  if(compare(angle1,0,15) && compare(angle2,0,10) && compare(angle3,65,12) && compare(angle4,90,20) && compare(angle5,85,15) && vertical){
    letter = "l";
  }

  if(compare(angle1,55,10) && compare(angle2,60,12) && compare(angle3,50,12) && compare(angle4,90,30) && !vertical ){
    letter = "m";
  }

  if(compare(angle1,40,10) && compare(angle2,80,7) && compare(angle3,70,10) && compare(angle4,90,15) && compare(angle5,90,30) && !vertical){
    letter = "n";
  }

  if(compare(angle1,65,15) && compare(angle2,55,15) && compare(angle3,40,15) && compare(angle4,40,15) && vertical){
    letter = "o";
  }
  
  if(compare(flexADC1,575,40) && compare(flexADC2,560,40) && compare(flexADC3,565,40) && compare(flexADC4,570,40) && compare(flexADC5,570,40) && equilibrium){
    letter = "p";
  }

  if(compare(flexADC1,590,40) && compare(flexADC2,520,40) && compare(flexADC3,390,40) && compare(flexADC4,365,40) && compare(flexADC5,400,40) && equilibrium){
    letter = "q";
  }

  if(compare(angle1,60,15) && compare(angle2,5,10) && compare(angle3,5,10) && compare(angle4,10,10) && compare(angle5,75,10)){
    letter = "w";
  }

  if(compare(angle1,90,25) && compare(angle2,40,10) && compare(angle3,70,10) && compare(angle4,90,10) && compare(angle5,90,10) && vertical){
    letter = "x";
  }

  if(compare(angle1,10,10) && compare(angle2,85,15) && compare(angle3,60,10) && compare(angle4,90,10) && compare(angle5,15,15)){
    letter = "y";
  }

  if(compare(flexADC1,515,40) && compare(flexADC2,558,40) && compare(flexADC3,385,40) && compare(flexADC4,375,40) && compare(flexADC5,380,40) && !horizontal){
    letter = "z";
  }

  if(compare(angle1,10,15) && compare(angle2,0,15) && compare(angle3,0,15) && compare(angle4,0,15) && compare(angle5,0,15) && vertical){
    letter = "_";
  }

  if(compare(angle1,10,10) && compare(angle2,0,15) && compare(angle3,65,10) && compare(angle4,90,10) && compare(angle5,0,10) && count == 0){
    str += lastletter;
    count = 1;
    bt.println(str);
  }

  if(lastletter != letter && !stringComplete){
    lastletter = letter;
    str += lastletter;
    count = 0;
    bt.println(str);
  }

  if(compare(angle1,70,15) && compare(angle2,5,15) && compare(angle3,60,15) && compare(angle4,5,15) && compare(angle5,5,15) && !sent){
    str += ".";
    Serial.println(str);
    sent = true;
  }

  if (stringComplete){
    bt.println(pyString);
    str = pyString;
    sent = false;
    stringComplete = false;
  }
  
  delay(500);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {              
      stringComplete = true;           
    } else {
      pyString += inChar;
    }
  }
}
