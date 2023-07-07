#include <LiquidCrystal_I2C.h>
#include <TimeLib.h> // Include the Time library
#include <Ultrasonic.h>

// Initialize LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the I2C address if necessary

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Create an Ultrasonic object
Ultrasonic ultrasonic(trigPin, echoPin);

// Alarm time variables
int alarmHour = 0;
int alarmMinute = 1;
bool alarmEnabled = false;

// Menu variables
int menu = 0;
int setHour = 0;
int setMin = 0;
int setAlarmHour = 0;
int setAlarmMin = 0;

//************Button*****************//
int P1=13; // Button SET MENU'
int P2=12; // Button +
int P3=11; // Button -
int P4=9; // SWITCH Alarm

int relay = 5;
int buzzer = 6;

void setup() {
  // Initialize LCD display
  lcd.begin(16, 2);
  lcd.clear();

  // Print initial message on the LCD
  lcd.setBacklight(1);
  lcd.setCursor(0, 0);
  setTime(0,0,50,day(),month(),year());
}

void loop() {
  // Read the current time
  int currentHour = hour();
  int currentMinute = minute();
  int currentSecond = second();

  // Display the current time on the LCD
  lcd.setCursor(0, 1);
  lcd.setBacklight(1);
  
  // Check if it's time for the alarm
  if (alarmEnabled && currentHour == alarmHour && currentMinute == alarmMinute) {
    activateAlarm();
  }else{
    noTone (buzzer);
  }

  // if (ultrasonic.read() < 10) {
  //   alarmEnabled = false;
  //   lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("Alarm Disabled");
  //   delay(1000);
  // }

  // Delay for 1 second
  delay(1000);

  if(digitalRead(P1)== HIGH){
   menu=menu+1;
   Serial.print("menu incremented");
  }
  // menu = 1;
  if(menu==0){ 
    lcd.clear();
    printTime(currentHour, currentMinute, currentSecond);
  }else if(menu == 1){
    displaySetHour();
  }else if(menu == 2){
    displaySetMin();
  }else if(menu == 3){
    displaySetAlarmHour();
  }else if(menu == 4){
    displaySetAlarmMin();
  }else if(menu == 5){
    saveAll();
  }

}

// Print the time on the LCD in the format HH:MM:SS
void printTime(int hours, int minutes, int seconds) {
  lcd.print("Time: ");
  
  if (hours < 10) {
    lcd.print("0");
  }
  lcd.print(hours);
  lcd.print(":");
  if (minutes < 10) {
    lcd.print("0");
  }
  lcd.print(minutes);
  lcd.print(":");
  if (seconds < 10) {
    lcd.print("0");
  }
  lcd.print(seconds);
}

// Check if the current time matches the set alarm time
void checkAlarm() {
  int currentHour = hour();
  int currentMinute = minute();

  if (alarmEnabled && currentHour == alarmHour || currentMinute == alarmMinute) {
    lcd.clear();
    lcd.print("ringing");
  }
}

// Activate the alarm (e.g., turn on a buzzer)
void activateAlarm() {
  // Implement your own logic here, such as turning on a buzzer
  // For simplicity, we'll just print a message on the LCD
  lcd.clear();
  lcd.setBacklight(1);
  lcd.print("ALARM");
  // delay(5000); // Delay for 5 seconds
  //lcd.print("Time:");

  tone(buzzer,880); //play the note "A5" (LA5)
  lcd.setBacklight(0);
  delay (300);
  tone(buzzer,698); //play the note "F6" (FA5)
  lcd.setBacklight(1);
}

void displaySetHour(){
  setHour = hour();
  if(digitalRead(P2)==HIGH){
    if(setHour==23){
      setHour=0;
    }
    else{
      setHour+=1;
    }
  }
  if(digitalRead(P3)==HIGH) {
    if(setHour==0){
      setHour=23;
    }
    else{
      setHour-=1;
    }
  }
  setTime(setHour,minute(),second(),day(),month(),year());

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Hour: ");
  lcd.print(setHour,DEC);

  //setTime(setHour,0,50,day(),month(),year());

  delay(200);

  // if(setHour == 5){
  //   menu=0;
  // }
  
}

void displaySetMin(){
  setMin = minute();
  if(digitalRead(P2)==HIGH){
    if(setMin==59){
      setMin=0;
    }
    else{
      setMin+=1;
    }
  }
  if(digitalRead(P3)==HIGH) {
    if(setMin==0){
      setMin=59;
    }
    else{
      setMin-=1;
    }
  }

  setTime(hour(),setMin,second(),day(),month(),year());

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Minute: ");
  lcd.print(setMin,DEC);

  //setTime(hour(),setMin,second(),day(),month(),year());

  delay(200);

  // if(setMin == 5){
  //   menu=0;
  // } 
}

void displaySetAlarmHour(){

  if(digitalRead(P2)==HIGH){
    if(alarmHour==23){
      alarmHour=0;
    }
    else{
      alarmHour+=1;
    }
  }
  if(digitalRead(P3)==HIGH) {
    if(alarmHour==0){
      alarmHour=23;
    }
    else{
      alarmHour-=1;
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Alarm Hour: ");
  lcd.setCursor(0, 1);
  lcd.print(alarmHour,DEC);
  
  delay(200);

  // if(alarmHour == 5){
  //   menu=0;
  // } 
}

void displaySetAlarmMin(){

  if(digitalRead(P2)==HIGH){
    if(setAlarmMin==59){
      setAlarmMin=0;
    }
    else{
      setAlarmMin+=1;
    }
  }
  if(digitalRead(P3)==HIGH) {
    if(setAlarmMin==0){
      setAlarmMin=59;
    }
    else{
      setAlarmMin-=1;
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Alarm Min. : ");
  lcd.setCursor(0, 1);
  lcd.print(setAlarmMin,DEC);
  delay(200);

  // if(setAlarmMin == 5){
  //   menu=0;
  // } 
}

void saveAll(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SAVING IN");
  lcd.setCursor(0,1);
  lcd.print("PROGRESS");
  
  setTime(setHour,setMin,second(),day(),month(),year());
  alarmHour = setAlarmHour;
  alarmMinute = setAlarmMin;

  delay(200);
  menu = 0;
}