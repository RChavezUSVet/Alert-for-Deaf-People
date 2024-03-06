/* 
 * Project Alert for deaf people
 * Author: Randall Chavez
 * Date: 03-04-2024
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h" 
#include "IoTClassroom_CNM.h"
#include <Encoder.h>
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include <neopixel.h>
#include <colors.h>
int motionPin = D4;
const int PINA = D8;
const int PINB = D9;

int position;
int lastPosition;

Encoder myEncoder(PINA, PINB);
Adafruit_SSD1306 display(-1);


int bri=255;
int val;
int myhue=4;
// 

SYSTEM_MODE(MANUAL);
bool buttonOnOff;
const int MYWEMO=3; 
Button wemoButton (D16);
SYSTEM_THREAD(ENABLED);
const int PIXELCOUNT = 16;
Adafruit_NeoPixel pixel ( PIXELCOUNT, SPI1, WS2812B) ;


void setup(){ 
  Serial.begin(9600); 
  waitFor(Serial.isConnected,10000);


  pinMode(motionPin, INPUT);
  WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
//setHue(myhue, false, HueRed, (255),255);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
 
  
  delay(5000);
pixel.begin();
 pixel.setBrightness (bri); 
 pixel.show();

 delay (2000);
}

void loop(){
  display.setCursor(0,0);
position = myEncoder.read ();
if (position != lastPosition)
{
Serial.printf("Encoder position: %i\n", position); 
lastPosition = position;
}



  val = digitalRead(motionPin);



if (val == HIGH){
  setHue(myhue, true, HueRed, (255),255);
  Serial.printf("motion detected --- val = %i\n", val);
  display.printf("Police Dispatched");
  display.display();
  display.clearDisplay();
}

else{ 
  setHue(myhue, false, HueRed, (255),255);       
  Serial. printf("no motion detected -- val = %i\n", val  );
  display.printf("All Clear");
  display.display();
  display.clearDisplay();
  }
  
  if(wemoButton.isClicked()){
    buttonOnOff=!buttonOnOff;
  }
  if(buttonOnOff==true){
    Serial.printf("Turning on Wemo# %i\n",MYWEMO);
    wemoWrite(MYWEMO,HIGH);
  }
  else{
    wemoWrite(MYWEMO,LOW);
    Serial.printf("Turning off Wemo# %i\n",MYWEMO);
  }

}


  


