#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'},
};
byte rowPins[ROWS] = {2,3,5,6};
byte colPins[COLS] = {7,8,9,4};

int V_LED = 11;
int R_LED = 13;
int myBuzzer = 10;

Servo myservo;
// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(14, 15, 16, 17, 18, 19);// RS-->A0 ,E-->A1,D4,D5,D6,D7
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins,
ROWS, COLS);


char PIN_User1[4]=  {'1','2','3','4'}; // secret number for user 1
char PIN_User2[4] = {'2','B','2','B'};
char PIN_User3[4] = {'A','B','C','D'};


char attempt[4]={0,0,0,0};
int z=0;
int try_s = 0;
int pos = 0; 
bool perDetect = false;

void init_lcd();
void notVerficated();
void verficated();


void readKeypad();
void setup() {
 init_lcd();
 myservo.attach(12); 
 myservo.write(0);
 pinMode(myBuzzer,OUTPUT);
 pinMode(V_LED,OUTPUT);
 pinMode(R_LED,OUTPUT);
 digitalWrite(V_LED, LOW);
 digitalWrite(R_LED, LOW);
 lcd.print("Enter Your Code :");

}
void User1_Come() {
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Welcome");
  lcd.setCursor(4,1);
  lcd.print("*User1*");
  delay(2000);
}
void User2_Come() {
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Welcome");
  lcd.setCursor(4,1);
  lcd.print("*User2*");
  delay(2000);
}
void User3_Come() {
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Welcome");
  lcd.setCursor(4,1);
  lcd.print("*User3*");
  delay(2000);
}

void errorPIN() {
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Invalid");
  lcd.setCursor(5,1);
  lcd.print("*Code*");
  delay(2000);
  if (try_s == 0) {
  lcd.clear();
  lcd.print("Enter Your Code :");
  }
}

void verificated() {
  digitalWrite(V_LED,HIGH);
  delay(1000);
  digitalWrite(V_LED,LOW);
  delay(1000);
  myservo.write(180);
  delay(2000);
  lcd.clear();
  lcd.print(" The Door ");
  lcd.setCursor(4,1);
  lcd.print(" Opened ");
  delay(2000);
  myservo.write(0);
  delay(1500);
  lcd.clear();
  lcd.print("Enter Your Code");
  perDetect = false;
}

void notVerficated() {
  
  digitalWrite(R_LED,HIGH);
  delay(1000);
  digitalWrite(R_LED,LOW);
  delay(1000);
  try_s = try_s +1;
  if ( try_s == 2) {
    lcd.clear();
    lcd.print(" ! Stranger ! ");
    digitalWrite(myBuzzer,HIGH);
    delay(1000);
    digitalWrite(myBuzzer,LOW);
    try_s = 0;
    delay(2000);
    lcd.clear();
    lcd.print("Enter Your Code");
    perDetect == false;
    
  }
}

void clearPIN(){
for (int zz=0; zz<4; zz++) // remove previously entered code attempt from
{
attempt[zz]=0;
}
}

void checkPINs()
      {
int correct_User1=0;
int correct_User2 = 0;
int correct_User3 = 0;
int i;
 for ( i = 0; i < 4 ; i++ )
{
  
 if (attempt[i]==PIN_User1[i]) 
{
correct_User1++;
}

if (attempt[i] == PIN_User2[i]) {
  correct_User2++;
}
if (attempt[i] == PIN_User3[i]) {
     correct_User3++;
}
}

if(correct_User1==4)
{
  

  User1_Come();
  verificated();
  try_s =0;
}
 else if (correct_User2 == 4 ) {
 
 

User2_Come();
verificated();
try_s =0;
}
 else if
(correct_User3 == 4) {
 
  User3_Come();
  verificated();
  try_s =0;
}
else  {
 errorPIN();
 notVerficated();
}

}


void init_lcd() {
  lcd.clear();
  lcd.print("Enter Your Code");
  lcd.begin(16, 2);
}
void readKeypad()
{
char key = keypad.getKey();
  if (key != NO_KEY) {
    
      lcd.setCursor(pos,1);
      lcd.print(key);
      pos = pos+1;
      
    switch(key){
      
      case '*' :
      z=0;
      pos = 0;
      init_lcd();
      lcd.print("Enter Your Code");
      break;
      
      case '#' :
      delay(100); // removes the possibility of switch bounce
      checkPINs();
      z=0;
      pos = 0;
      break;
      default :
      attempt[z]=key;
      z++;
      break;
  }
  }
}
void loop(){
  readKeypad();
}
