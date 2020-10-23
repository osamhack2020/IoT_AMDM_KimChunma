#include <Servo.h>
#include <Wire.h>

#define SLAVE 3//슬레이브 아두이노 주소

#define STX	0x02
#define ETX	0x03

Servo servo_3;
Servo servo_5;
Servo servo_6;
Servo servo_9;


int Sense_Flag[4] = {0,};
int Master = 0;

char Read_Data[10] = {0,};  


void setup()
{
  	Serial.begin(9600);
  
  	//서보 모터 초기화
	servo_3.attach(3);
    servo_5.attach(5);
    servo_6.attach(6);
    servo_9.attach(9);
  
  	//서보 모터 각도 초기화
  	Init_servo(0);
  
  	//SPI 통신 초기화
    Wire.begin(SLAVE);  
  	Wire.onReceive(receiveEvent);      	    	
}

void loop()
{  	
      	
}

void Init_servo(int value){//서보 모터 각도 초기화 함수
	servo_3.write(value);
  	servo_5.write(value);
  	servo_6.write(value);
  	servo_9.write(value);
  
  	delay(1000); 	
}

void Initialize(){//변수 초기화 함수
  Master = 0;

  for(int i =0; i<8; i++){
  	if(i<4) Sense_Flag[i] = 0;
    Read_Data[i] = 0;
  }  
}


void receiveEvent(int sizeData){//수신데이터 분석 및 동작 함수      
  
  Initialize();
  
  if(Wire.available() > 0){//데이터 리딩
    for(int i = 0; i<sizeData; i++) {Read_Data[i] = Wire.read();}
    Serial.println(sizeData);    
    Serial.println(Read_Data);    
  }
   
  if(Read_Data[0] == STX && Read_Data[7] == ETX){//수신 데이터 확인
  	
    if(Read_Data[4]){//보관함 번호 확인
      if(Read_Data[4] == '0'){Sense_Flag[0] = 1;}  
      else if(Read_Data[4] == '1'){Sense_Flag[1] = 1;}    	
      else if(Read_Data[4] == '2'){Sense_Flag[2] = 1;}  
      else if(Read_Data[4] == '3'){Sense_Flag[3] = 1;}  	
      else if(Read_Data[4] == 'A'){Master = 1;}


      if(Read_Data[5] == 'O' && Read_Data[6] == 'P'){//동작 확인 (개방일 경우 제약조건없이 바로 개방)         
        if(Sense_Flag[0]) 		{servo_3.write(0);}
        else if(Sense_Flag[1]) 	{servo_5.write(0);}
        else if(Sense_Flag[2]) 	{servo_6.write(0);}
        else if(Sense_Flag[3]) 	{servo_9.write(0);}
        else if(Master == 1)		{Init_servo(0);}//전체보관함 동작

      }

      else if(Read_Data[5] == 'C' && Read_Data[6] == 'L'){//동작 확인 (폐쇄일 경우 휴대전화가 반납된 것을 조도센서로 확인후 폐쇄)   
        while(Sense_Flag[0] || Sense_Flag[1] || Sense_Flag[2] || Sense_Flag[3]){
          if(Sense_Flag[0] && analogRead(A0) < 700) 		{servo_3.write(45); break;}
          else if(Sense_Flag[1] && analogRead(A1) < 700) 	{servo_5.write(45); break;}
          else if(Sense_Flag[2] && analogRead(A2) < 700) 	{servo_6.write(45); break;}
          else if(Sense_Flag[3] && analogRead(A3) < 700) 	{servo_9.write(45); break;}
          else if(Master == 1)							{Init_servo(45); break;}//전체보관함 동작      
        }      
      }        
    } 
  }
}


