## AMDM(Army Mobile Device Management)
저희는 RFID 기술을 이용한 IoT 장치와 휴대전화를 통제하는 APP을 개발하여 군에서의 보안/안전적인 측면을 더욱 강화시키는 것 뿐만아니라 전군 장병들의 휴대폰 관리를 전산화 처리를 할려고 합니다.
저희 팀은 국방 오픈소스 아카데미에 참가하여 국군 모바일 단말 장치 관리 시스템(Army Mobile Device Management System)을 구현시키고자 합니다. 🔥

### 로고

![Logo](https://github.com/yeonghokim/AMDM/blob/main/logo/Logo_Github.png)

<p align="center">AMDM의 로고는 초승달과 자물쇠가 합쳐서 좋은 밤을 위해서는 보안을 잠그자 라는 뜻을 의미하고 있습니다.</p>

## 팀소개 및 프로젝트 설명 동영상 👍
[![AMDM 프로젝트 발표자료(최종본)_22](https://user-images.githubusercontent.com/71952165/97779919-a1fa2f80-1bc4-11eb-9d8d-1fddcd1b012c.png)](https://youtu.be/HRwMVqA-am0)


## 기능 설계
 - [안드로이드 디자인 Kakao Oven](https://ovenapp.io/project/qREXQacVLW1qzBvL5xhXo0wNgUoqVt7W#ScIyR)
 - [아두이노 시뮬레이팅 Thinker CAD](https://www.tinkercad.com/things/cZuXuEFHrnm)
## 구성 / 필수 조건 안내 (Prerequisites)
* Android 6.0 (Marshmallow) 이상 
* 휴대폰 NFC, 인터넷 기능 필수
* Python3.0 이상 필요
* AMDMServer가 실행되어있어야 정상적으로 작동함

## 기술 스택 (Technique Used)
### Server(back-end)
 - Python 3버전을 통해 개발
 - TCP 소켓 통신 서버
 - SQLite로 DB 구현

### IoT
 - 아두이노를 중심으로한 잠금장치 구현(조도센서,서보모터 이용)
 - 라즈베리 ↔ 아두이노 간 I2C 통신을 통한 Master-Slave 아키텍처 구현
 - 라즈베리 TCP 클라이언트 구현

### Android
 - *Fragment*를 통하여 메인화면 구현
 - *BroadCast Receiver*를 통해 안드로이드 켜질시 상태 구현
 - chart 구현을 위해 [MPAndroidChart](https://github.com/PhilJay/MPAndroidChart)를 사용하여 구현
 - Lock구현을 위해 Screen 없애질때마다 커스텀 액티비티로 대체함
 - TurnOnService 서비스 구현

## 시스템 아키텍처 (System Architecture)
![AMDM 프로젝트 발표자료(최종본)_7](https://user-images.githubusercontent.com/71952165/97780042-87748600-1bc5-11eb-86f2-4142215e727b.png)

## 시스템 라이프사이클 (System LifeCycle)
 ### 반납 사이클
 ![AMDM 프로젝트 발표자료(최종본)_9](https://user-images.githubusercontent.com/71952165/97780081-c73b6d80-1bc5-11eb-9a8c-2f6a5620f3ce.png)
 
 ### 불출 사이클
![AMDM 프로젝트 발표자료(최종본)_8](https://user-images.githubusercontent.com/71952165/97780072-ba1e7e80-1bc5-11eb-83ff-be0d3e93e655.png)

## 설치 안내 (Installation Process)

### Android apk 실행
* ${Git Home}/app-debug.apk

### Python 서버 실행
```bash
$ python3 ${Git Home}/AMDMServer/server.py
```

### SQLite 실행(필요시)
```bash
$ sqlite3
$ .open AMDMserver.sqlite3
```

## 프로젝트 사용법 (Getting Started)
1. [Android](https://github.com/yeonghokim/AMDM#android-1)
2. [Server](https://github.com/yeonghokim/AMDM#server)
3. [IoT장비와 데이터 교환](https://github.com/yeonghokim/AMDM#iot%EC%9E%A5%EB%B9%84-%EB%8D%B0%EC%9D%B4%ED%84%B0-%EA%B5%90%ED%99%98)
4. [Android와 데이터 교환](https://github.com/yeonghokim/AMDM#android-%EB%8D%B0%EC%9D%B4%ED%84%B0-%EA%B5%90%ED%99%98)
5. [DataBase(SQLite)](https://github.com/yeonghokim/AMDM#database-sqlite)

## Android
#### 화면 리스트
* SplashActivity
* LoginMainActivity
* LoginActivity
* MainActivity
    * MainLockFragment
    * MainSetupFragment
    * MainStaticsFragment
* TurnOnActivity
* TurnOnReceiver
* LockService
#### 참고사항
* 로그인 ID: admin PW: admin
* 서버통신 대체 : 3초 대기
* RFID 태그 대체 : 3초 대기

## Server
* Python3으로 이루어진 TCP 소켓 서버입니다.

### 코드 소개
1. logs 폴더
    * 서버의 로그를 저장하는 폴더입니다. D로 시작하면 Default, W로 시작하면 Warning, E로 시작하면 Error를 뜻합니다.
2. util 폴더
    * 서버의 전반적인 유틸에 관한 코드입니다.
    * DBManager.py는 SQLite와 연결하기 위한 코드입니다.
    * jsonManager.py는 데이터와 Json 끼리 교환하기 위한 코드입니다.
    * serverLog.py는 로그저장하는 코드입니다.
    * ServerTime.py는 서버의 시간을 체크하는 코드입니다.
    
## IoT장비 데이터 교환
참고 : [데이터 교환.txt](https://github.com/osamhack2020/APP_AMDM_KimChunma/blob/main/%EB%8D%B0%EC%9D%B4%ED%84%B0%20%EA%B5%90%ED%99%98.txt)

## DataBase (SQLite)
참고 : [데이터베이스 스키마.txt](https://github.com/osamhack2020/APP_AMDM_KimChunma/blob/main/%EB%8D%B0%EC%9D%B4%ED%84%B0%EB%B2%A0%EC%9D%B4%EC%8A%A4%20%EC%8A%A4%ED%82%A4%EB%A7%88.txt)


## 팀 정보 (Team Information) 💙
- 김영호 (yeongho.kim2000@gmail.com), Github Id: yeonghokim
- 부규필 (qfeel0812@gmail.com), Github Id: Qfeel-Dev

## 저작권 및 사용권 정보 (Copyleft / End User License)
#### 이미지
 * [LockIcon](https://www.flaticon.com/free-icon/lock_3039495?term=lock&page=1&position=65)
 * [MoonIcon](https://www.flaticon.com/free-icon/moon_1030337?term=moon&page=2&position=85)
#### 코드
 * [linechart](https://github.com/PhilJay/MPAndroidChart)
  Copyright ⓒ 2020 Philipp Jahoda
  http://www.apache.org/licenses/LICENSE-2.0
  Apache License 2.0
 * [tcp](https://github.com/DDANGEUN/TCP_ClientSocket/tree/master)
 * [NFC](https://github.com/codexpedia/android_nfc_read_write)
