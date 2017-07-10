/* Doro FoodCube Version1 */
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 9, 10, 8);
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t oldax;
int16_t gx, gy, gz;

char* Pasta[14] = 
  { "Abachini", 
    "Bavette", 
    "Canalini", 
    "Cannelloni",
    "Conchiglioni",
    "Farfalle",
    "Fusilli",
    "Gnocchi",
    "Linguine",
    "Maccheroni",
    "Penne",
    "Spaghetti",
    "Spiralini",
    "Tortellini"
};

char* Sossen[9] =
 { "TomatenSauce",
   "KnoblauchSauce",
   "GemueseSauce",
   "PilzSauce",
   "Fleischsauce",
   "KaeseSauce",
   "FischSauce",
   "MeeresfruechteSauce",
   "PestoSauce"
};


/* ###########################################*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(); // pixel on
  display.setContrast(40);
  display.clearDisplay();
  DrawWelcome();
  delay(2000);
  
  Wire.begin();
  Serial.begin(9600);

  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  
}
void DrawWelcome()
{
  
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(13,8); // x y 
  display.println("Doros");
  display.setTextSize(1);
  display.setCursor(14,30);
  
  display.println("Food Cube");
  display.display();
  
 

}

void DrawSexWithUli()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(20,8); // x y 
  display.println("SEX");
  display.setTextSize(2);
  display.setCursor(0,30);
  
  display.println("mit Uli");
  display.display();
  
}
void DrawSelectedFood(String pasta, String sosse)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(3,8); //x ; y 
  display.println(pasta);
  //display.drawLine(10, 24, 74, 24, BLACK);
  display.setCursor(30,20);
  display.println("mit");
  display.setCursor(0,30);
  display.println(sosse);
  display.display();
  
 
}


void loop() {
  
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  String spasta, ssosse = "";
  int delta = oldax -ax;
  Serial.print("delta: ");
  Serial.println(delta);
  if (delta > 2000 || delta < -2000 )
  {
    if ((delta > 3000 && delta < 4000) || (delta > -3000  && delta < -4000))
    {
       DrawSexWithUli();
       delay(10000);
     }
     else 
    { 
     randomSeed(analogRead(0));
     int randp = random(0, 13);
     spasta = Pasta[randp];
     int rands = random(0, 8);
      ssosse = Sossen[rands];
      
      
      Serial.println("Pasta: ");
      Serial.print(randp);
      Serial.println(spasta);
      
      Serial.println("Sosse: ");
      Serial.println(rands);
      Serial.println(ssosse);
      DrawSelectedFood(spasta,ssosse);
      delay(400);   
    }
  }
  
   oldax = ax;
   
}


