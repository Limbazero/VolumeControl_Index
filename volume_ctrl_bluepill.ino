#include <USBComposite.h>


#define BUTTON_VOLUP   PB10
#define BUTTON_VOLDOWN PB11
#define DEBUG_LED      PC13

USBHID HID;

bool Pressed_down = false;
bool Pressed_up   = false;


const uint8_t reportDescription[] = {
   HID_CONSUMER_REPORT_DESCRIPTOR()
};

HIDConsumer Consumer(HID);

void setup(){
  HID.begin(reportDescription, sizeof(reportDescription));

  pinMode(BUTTON_VOLUP,   INPUT_PULLUP);
  pinMode(BUTTON_VOLDOWN, INPUT_PULLUP);
  pinMode(DEBUG_LED,      OUTPUT);

}

void loop() {

  if(!Pressed_down)
  {    
    if(digitalRead(BUTTON_VOLDOWN))
    {
      digitalWrite(DEBUG_LED, 1);
      Consumer.press(HIDConsumer::VOLUME_DOWN);
      Pressed_down = true;
    }
  } 
      
  if(!Pressed_up)
  {
    if (digitalRead(BUTTON_VOLUP))
    {
      digitalWrite(DEBUG_LED, 1);
      Consumer.press(HIDConsumer::VOLUME_UP);
      Pressed_up = true;
    }
  }
  

  if(Pressed_up or Pressed_down)
  {
    delay(100);
    if(!digitalRead(BUTTON_VOLUP) and !digitalRead(BUTTON_VOLDOWN))
    {
        Consumer.release();
        Pressed_up = false;
        Pressed_down = false;
    }
  }

  // Debug. Led on when no buttons pressed
  if(!Pressed_up and !Pressed_down)
    digitalWrite(DEBUG_LED, 0);

}
