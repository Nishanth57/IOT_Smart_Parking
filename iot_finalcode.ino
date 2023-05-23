#include <MFRC522.h>

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
//#include <MFRC522.h>

#define ir_1 6
#define ir_2 7 
#define ir_e 5 
#define ir_b 4


#define SS_PIN 10
#define RST_PIN 9
String UID = "DC D5 EB 38";


Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);

int s1=0, s2=0, se=0, sb=0;
int flag1=0, flag2=0;
int slot=2;



void setup() {
  Serial.begin(9600);
  
  pinMode(ir_1, INPUT);
  pinMode(ir_2, INPUT);
  pinMode(ir_e, INPUT);
  pinMode(ir_b, INPUT);
  
  myservo.attach(3); 
  myservo.write(90);
  lcd.init();
  lcd.backlight();


  lcd.begin(20,4);
  lcd.setCursor(2,1);
  lcd.print("  car parking  ");
  lcd.setCursor(2,2); 
  lcd.print("   system  ");
  delay(2000);
  lcd.clear();
       


  
  SPI.begin();
  rfid.PCD_Init(); 

  Read_Sensor();

  int total = s1+s2;
  slot = slot-total;
}

void loop() {
  
  Read_Sensor();
  
  
  lcd.setCursor(2,0);
  lcd.print("  Have Slot: ");
  lcd.print(slot);
  lcd.print("  ");
  lcd.setCursor(0,1);
  if(s1==1){lcd.print("s1:Fill ");}
      else{lcd.print("s1:Empty");}
  
  

  lcd.setCursor(10,1);
  if(s2==1){lcd.print("s2:Fill ");}
      else{lcd.print("s2:Empty");}
  

  


    lcd.setCursor(4,2);lcd.print("           ");
    if(digitalRead(ir_e)==0 && flag1==0){
    
      if(slot>0){flag1=1;
      if(flag2==0){
  //
if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  lcd.setCursor(4, 3);
  lcd.print("Scanning");

  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {

    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
    lcd.setCursor(4,3); 
    lcd.print("         ") ;      
          
  }
  ID.toUpperCase();      
        
        if (ID.substring(1) == UID )
        {myservo.write(180);
      slot=slot-1;
      delay(1000);}else{flag1=0;lcd.setCursor(4,2);lcd.print("not allowed");
      delay(600);
      flag2=1;
    
     
      }
 return;      
      

      }
      }else{
        lcd.setCursor (0,0);
        lcd.print("sorry parking full");
        
        delay(1500); 
        lcd.clear();
         }
    }

    
    if(digitalRead(ir_b)==0 && flag2==0){flag2=1;
    if(flag1==0){myservo.write(180);slot=slot+1;}
    }



    if(flag1==1 && flag2==1){
      delay(1000);
      myservo.write(90);
      flag1=0,flag2=0;
    }
  delay(1);  

  }

  


void Read_Sensor(){
  s1=0, s2=0;
if(digitalRead(ir_1)==0)(s1=1);
if(digitalRead(ir_2)==0)(s2=1);

}