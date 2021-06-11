#include <LiquidCrystal.h>

#define CHARGE_EN_PIN 12
#define LOAD_EN_PIN 11

#define V_PANEL_IN A0
#define R1 10000.0
#define R2 1000.0

#define V_BAT_IN A1
#define R3 10000.0
#define R4 1000.0

#define DISPLAY_INTERVAL 50
#define MEASURE_INTERVAL 50

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

float panel_voltage = 0.0;
float vin_panel = 0.0;
float battery_voltage = 0.0;
float vin_bat = 0.0;
long display_millis=0;
long measure_millis=0;


void setup() {
       pinMode(CHARGE_EN_PIN, OUTPUT);
  digitalWrite(CHARGE_EN_PIN, HIGH);
       pinMode(LOAD_EN_PIN,   OUTPUT);
  digitalWrite(LOAD_EN_PIN,   HIGH);
  
  lcd.begin(16,2); 
  
  measure_millis=millis();
  display_millis=millis();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  Panel:");
  lcd.setCursor(0,1);
  lcd.print("Battery:");
}

void loop() {
  
  
  if (millis()>(measure_millis+MEASURE_INTERVAL))
  {
    measure_millis=millis();
    
    vin_panel = (analogRead(V_PANEL_IN)*5.0)/1024.0;
    panel_voltage = vin_panel/(R2/(R1+R2));  

    vin_bat = (analogRead(V_BAT_IN)*5.0)/1024.0;
    battery_voltage = vin_bat/(R4/(R3+R4));  

    
    if (battery_voltage>14.4)digitalWrite(CHARGE_EN_PIN, LOW); else digitalWrite(CHARGE_EN_PIN, HIGH);  //to do : add hysteresis
    if (battery_voltage<10)digitalWrite(LOAD_EN_PIN, LOW);   else digitalWrite(LOAD_EN_PIN, HIGH);    //to do : add hysteresis
  }
    
    
  if (millis()>(display_millis+DISPLAY_INTERVAL))
  {
    display_millis=millis();
    
    lcd.setCursor(9,0);
    lcd.print(panel_voltage);
    lcd.print("V ");
    lcd.setCursor(9,1);
    lcd.print(battery_voltage);
    lcd.print("V ");
  }

}
