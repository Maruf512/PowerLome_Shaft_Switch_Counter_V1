// include library
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address for a 16 chars and 2 line display

//Global Veriables (Fixed Value)
const int notPressedBtn = 8;
const int pressedCountBtn = 9;
const int counterSwitchPower = 10;
const int relayPin = 2;

//Global Veriables (Changable)
int counter = 0;                              // value will constantly change
int targetValue = 10;
int relayS = 0;
int relyState[] = {0,0,0,1,1,1,1,0,1,0};

bool switchState = false;
// ======================================= Setup Function ================================
void setup() {
  // initialize the Counter Button's pin as an Input
  pinMode(notPressedBtn, INPUT);
  pinMode(pressedCountBtn, INPUT);
  pinMode(counterSwitchPower, OUTPUT);        // asign it as output to push power through the switch
  pinMode(relayPin, OUTPUT);

  // turn off the relay
  digitalWrite(relayPin, HIGH);
  // Turn The light's off to save power
  digitalWrite(13, LOW);

  // for display
  lcd.init();
  lcd.clear();
  lcd.backlight();                                // Make sure backlight is on
  

  digitalWrite(counterSwitchPower, LOW);

  
  // to test only
  Serial.begin(9600);

  // startup
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Initiating:");
  delay(300);
  lcd.setCursor(11,0);
  lcd.print("#");
  delay(300);
  lcd.setCursor(12,0);
  lcd.print("#");
  delay(300);
  lcd.setCursor(13,0);
  lcd.print("#");
  delay(300);
  lcd.setCursor(14,0);
  lcd.print("#");
  delay(300);
  lcd.setCursor(15,0);
  lcd.print("#");
  delay(300);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Loading Program");

  for(int i = 0; i <= 15; i++){
    lcd.setCursor(i,1);
    lcd.print("#");
    delay(100);
  }

  for(int i =0; i<=15; i++){
    lcd.setCursor(i,1);
    lcd.print(" ");
  }

  lcd.setCursor(6,1);
  lcd.print("Done");
  delay(1000);

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("EDITH");
  lcd.setCursor(0,1);
  lcd.print("Created By Maruf");

}

// ======================================= Counter Function ==============================
void SwitchingCount(){
  int pushedState = digitalRead(pressedCountBtn);
  int releasedState = digitalRead(notPressedBtn);
  if(pushedState == HIGH &&  releasedState == LOW){
    if(switchState == true){
      counter += 1;
      switchState = false;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Counter: ");
      lcd.setCursor(9,0);
      lcd.print(counter);
      // view target
      lcd.setCursor(0,1);
      lcd.print("Target: ");
      lcd.setCursor(9,1);
      lcd.print(targetValue);
    }
  }
  if(releasedState == HIGH && pushedState == LOW){
    switchState = true;
    digitalWrite(relayPin, HIGH);
  }
}
// ======================================= Main Loop =====================================
void loop() {
  SwitchingCount();
  Serial.println(counter);

  if(counter < targetValue){
    if(relyState[counter] == 1){
      if(relayS == 0){
        digitalWrite(relayPin, LOW);
        delay(50);                        // Relay On Time
        relayS = 1;
      }
      
      
    }
    else{
      digitalWrite(relayPin, HIGH);
      relayS = 0;
    }
  }
  else{
    digitalWrite(relayPin, HIGH);
    relayS = 0;
  }

  if(counter == 0){
    digitalWrite(relayPin, HIGH);
    relayS = 0;
  }

  // Create a loop of Counter wien it reaches the main Target
  if(counter == targetValue){
    counter = 0;
  }
  
  
}
