#include <IRremote.h>
#include <Wire.h>

#define STX	0x02
#define ETX	0x03


//프로토콜 정의(간략)
//1,2,3번째 자릿수 타겟 아두이노(범위: 000 ~ 120) 
//4번째 자릿수 보관함 넘버(범위: 0 ~ 4)
//5,6번째 자릿수 동작 (OP,CL)


//전역 변수 및 센서 셋팅
IRrecv irrecv(12);
decode_results results;

char Data_Parse[8] = {0,};
char Read_Data[20] = {0,};

int Target = 0;


void setup() {
  Wire.begin(); // Wire 라이브러리 초기화 //마스터 지정
    
  Serial.begin(9600); // 직렬 통신 초기화
  irrecv.enableIRIn();//적외선 센서 활성화   
  
  Serial.println("Master Initialize end");       
}

void loop() {
    
  if(irrecv.decode(&results)){//RFID 테그 입력  	
  	
    //Serial.println(results.value);    
    
    Change_Hex(results.value);//10진수 입력 신호를 데이터 파싱을 위한 16진수로 변환
    
    Data_Parse[0] = STX;//프로토콜 시작신호 알림
    
    //Read_Data[2~4]를 이용한 타겟 아두이노 데이터 파싱
    if(Read_Data[2] && Read_Data[3] && Read_Data[4]){                  
      	//팅커캐드 RFID 모듈 미지원으로 인한 임의 기준으로 데이터 파싱      
		if(Read_Data[2] == 'F'){Data_Parse[1] = '0'; Data_Parse[2] = '0'; Target += 0;}      	
		
      	for(int i = 0; i<10; i++){
        	if(int(Read_Data[3]) == 65+i){Data_Parse[3] = char(48+i); Target += i;}      	      
		}      	      
    }
    
    //Read_Data[5] 를 이용한 보관함 넘버 확인
    if(Read_Data[5]){
      	//팅커캐드 RFID 모듈 미지원으로 인한 임의 기준으로 데이터 파싱
      	Data_Parse[4] = '0';      
	}
    
    //Read_Data[6~7] 를 이용한 보관함 보관함 동작 확인
    if(Read_Data[6] && Read_Data[7]){
		//팅커캐드 RFID 모듈 미지원으로 인한 임의 기준으로 데이터 파싱      
      	if(int(Read_Data[6] + Read_Data[7]) > 110) {Data_Parse[5] = 'O'; Data_Parse[6] = 'P';} // open
      	else if(int(Read_Data[6] + Read_Data[7]) <= 110) {Data_Parse[5] = 'C'; Data_Parse[6] = 'L';} // close    
    }
     
    Data_Parse[7] = ETX;//프로토콜 종료 신호 알림
    
    Send_Data(Data_Parse,Target);//생성된 프로토콜 타겟 아두이노로 전달
     
        
    for(int i = 0; i<8; i++){
      Serial.print(Data_Parse[i]);      
    }
  	Serial.println();
	
    delay(30);
    irrecv.resume();//재수신을 위한 초기화
  }
}

void Send_Data(char c[],int des){//데이터 송신 함수(마스터 아두이노 -> 타겟)(1.보낼 데이터 2.타겟 아두이노 주소)
    Wire.beginTransmission(des);
    Wire.write(c);
    Wire.endTransmission();  
}

void Initialize(){//변수 버퍼 초기화	
  	for(int i = 0; i<20; i++) Read_Data[i] = 0;
  	Target = 0;
}

int Change_Hex(unsigned long decimal){//16진수 변환 함수 	
  	Initialize();
  
  	unsigned long target_num = decimal;
  	int num;
  	int position = 7;
  
    while(1){                                   
      num = target_num%16;   
      
      if (num < 10) {            
        Read_Data[position] = 48 + num;
      }
      else {            
        Read_Data[position] = 65 + (num - 10);
      }
            
      if(target_num/16 == 0) {break;}
      
      position--;
      target_num = target_num/16;            
    }    
  
  	return 0;
}


