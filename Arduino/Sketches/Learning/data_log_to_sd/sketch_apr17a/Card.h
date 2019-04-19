#include <SD.h>
#include "FlashingLed.h"

/*
 * Class to handle SD Card read and writes.
 */

class Card {

  private:
  int CS_PIN = 0;
  int LED_PIN = 0;
  File file;
  FlashingLed led;

  public:

  Card() {
    
  }

  

  bool Initialise(int cs_pin, int led_pin)
  {
    CS_PIN = cs_pin;
    LED_PIN = led_pin;
    Serial.println(led_pin);
    led.Init(LED_PIN, 50, 50);
    led.On();
    Serial.println("Initializing SD card...");
    pinMode(CS_PIN, OUTPUT);

    if (SD.begin())
    {
      led.Off();
      Serial.println("SD card is ready to use.");
      return true;
    }
    led.Off();
    Serial.println("SD card initialization failed");
    return false;  
  }

  bool OpenFile(String filename)
  {
    led.On();  
    file = SD.open(filename);
    if (file)
    {
      Serial.print("File '");
      Serial.print(filename);
      Serial.println("' opened.");
      led.Off();
      return true;
    }
    Serial.print("Error opening file '");
    Serial.print(filename);
    Serial.println("'....");
    led.Off();
    return false;   
  }

  bool CreateFile(String filename)
  {
    led.On();
    file = SD.open(filename, FILE_WRITE);

    if (file)
    {
      Serial.println("File created successfully.");
      led.Off();
      return true;
    }
    Serial.println("Error while creating file.");
    led.Off();
    return 0; 
  }

  
  bool WriteToFile(String text)
  {
    led.On();
    if (file)
    {
      file.println(text);
      led.Off();
      return true;
    }
    
    Serial.println("Unable to write to file");
    led.Off();
    return false;  
  }

  String ReadLine()
  {
    led.On();
    String received = "";
    char ch;
    while (file.available())
    {
      ch = file.read();
      if (ch == '\n')
      {
        return String(received);
        led.Off();
      }
      received += ch;
    }
    led.Off();
    return "";
  }

  void CloseFile()
  {
    led.On();
    if (file)
    {
      file.close();
      Serial.println("File closed");
    }
    led.Off();
  }
 


  

};
