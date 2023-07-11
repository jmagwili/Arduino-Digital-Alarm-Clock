#include <LiquidCrystal_I2C.h>
#include <TimeLib.h> // Include the Time library
#include <Ultrasonic.h>

// Initialize LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Create an Ultrasonic object
Ultrasonic ultrasonic(trigPin, echoPin);

// Alarm time variables
int alarmHour = 0;
int alarmMinute = 1;
bool alarmEnabled = true;

// Menu variables
int menu = 0;
int setHour = 0;
int setMin = 0;
int setAlarmHour = 0;
int setAlarmMin = 0;

//************Button*****************//
int P1=13; // Button SET MENU'
int P2=12; // Button + (Change to PIN 12)
int P3=11; // Button -
int P4=5; // SWITCHAlarm (Change to PIN 8)

int relay = 5;
int buzzer = 6;

// Object detection variables
bool objectDetected = false;
unsigned long objectDetectedStartTime = 0;

unsigned long prevTime_T1 = millis();
unsigned long prevTime_T2 = millis();

void setup() {
  // Initialize LCD display
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Print initial message on the LCD
  lcd.setBacklight(1);
  lcd.setCursor(0, 0);
  setTime(0,0,50,day(),month(),year());
}

void loop() {
  unsigned long currentTime = millis();

  int currentHour;
  int currentMinute;
  int currentSecond;

  if(currentTime - prevTime_T1 > 1000){
    // Read the current time
    currentHour = hour();
    currentMinute = minute();
    currentSecond = second();

    lcd.setCursor(0, 1);
    lcd.setBacklight(1);

    if(menu == 0){
      lcd.clear();
      printTime(currentHour,currentMinute,currentSecond);
    }
    prevTime_T1 = currentTime;
  }
   
  if(digitalRead(P1)== HIGH){
   menu=menu+1;
  }
  if(digitalRead(P4)== HIGH){
    lcd.clear();
    lcd.setCursor(0, 0);
    
    if(alarmEnabled){
      alarmEnabled = false;
      lcd.print("ALARM DISABLED");
    }else{
      alarmEnabled = true;
      lcd.print("ALARM ENABLED");
    }
    delay(1000);
  }

  if(menu == 1){
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

  //  if (ultrasonic.read() < 10) {
  //     Serial.println("detected");
  //   }

  //Check if it's time for the alarm
  if (alarmEnabled && currentHour == alarmHour && currentMinute == alarmMinute) {
    if (isObjectDetected()) {
      alarmEnabled = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alarm Disabled");
      delay(1000);
      noTone(buzzer);
    } else {
      activateAlarm();
    }
  }
  noTone(buzzer);

  if(isObjectDetected()){
    Serial.println("detected");
    //delay(500);
  }
}

bool isObjectDetected() {
  // Measure the distance using the ultrasonic sensor
  unsigned long currentTime = millis();
  unsigned int distance = ultrasonic.read();

  // Check if an object is within a specific range
  if (distance < 10) { // Adjust the threshold based on your needs
    return true;
  } else {
    return false;
  }
}

// Print the time on the LCD in the format HH:MM:SS
void printTime(int hours, int minutes, int seconds) {
  
  lcd.print("TIME:  ");

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

  lcd.setCursor(0, 1);
  lcd.print("ALARM: ");
  
  if (alarmHour < 10) {
  lcd.print("0");
  }
  lcd.print(alarmHour);
  
  lcd.print(":");
  
  if (alarmMinute < 10) {
    lcd.print("0");
  }
  lcd.print(alarmMinute);

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
  lcd.clear();
  lcd.setBacklight(1);
  lcd.print("ALARM");
  // delay(5000); // Delay for 5 seconds
  //lcd.print("Time:");

  tone(buzzer,880);
  lcd.setBacklight(0);
  delay (300);
  tone(buzzer,698);
  lcd.setBacklight(1);
  delay(1000);
}

void displaySetHour(){
  unsigned long currentTime = millis();
  
  setHour = hour();

  if(digitalRead(P2)==HIGH){
    lcd.clear();
    if(setHour==23){
      setHour=0;
    }
    else{
      setHour+=1;
    }
  }
  if(digitalRead(P3)==HIGH) {
    lcd.clear();
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

  delay(500); 
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

  delay(500);
}

void displaySetAlarmHour(){

  if(digitalRead(P2)==HIGH){
    if(alarmHour==23){
      setAlarmHour=0;
    }
    else{
      setAlarmHour+=1;
    }
  }
  if(digitalRead(P3)==HIGH) {
    if(alarmHour==0){
      setAlarmHour=23;
    }
    else{
      setAlarmHour-=1;
    }
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Alarm Hour: ");
  lcd.setCursor(0, 1);
  lcd.print(setAlarmHour,DEC);
  
  delay(500);
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
  delay(500);
}

void saveAll(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SAVING IN");
  lcd.setCursor(0,1);
  lcd.print("PROGRESS");
  
  setTime(setHour,setMin,0,day(),month(),year());
  alarmHour = setAlarmHour;
  alarmMinute = setAlarmMin;
  alarmEnabled = true;

  delay(1000);
  menu = 0;
}