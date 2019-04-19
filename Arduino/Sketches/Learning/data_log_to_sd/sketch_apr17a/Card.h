#include <SD.h>

/*
 * Class to handle SD Card read and writes.
 */

class Card {

  int CS_PIN = 0;
  File file;

  public:
  Card(int cs_pin) {
    CS_PIN = cs_pin;
  }


  bool Initialise()
  {
    Serial.println("Initializing SD card...");
    pinMode(CS_PIN, OUTPUT);

    if (SD.begin())
    {
      Serial.println("SD card is ready to use.");
      return true;
    }
    Serial.println("SD card initialization failed");
    return false;  
  }

  bool OpenFile(String filename)
  {
      
    file = SD.open(filename);
    if (file)
    {
      Serial.print("File '");
      Serial.print(filename);
      Serial.println("' opened.");
      return true;
    }
    Serial.print("Error opening file '");
    Serial.print(filename);
    Serial.println("'....");
    return false;   
  }

  bool CreateFile(String filename)
  {
    file = SD.open(filename, FILE_WRITE);

    if (file)
    {
      Serial.println("File created successfully.");
      return true;
    }
    Serial.println("Error while creating file.");
    return 0; 
  }

  
  bool WriteToFile(String text)
  {
    if (file)
    {
      file.println(text);
      return true;
    }
    
    Serial.println("Unable to write to file");
    return false;  
  }

  String ReadLine()
  {
    String received = "";
    char ch;
    while (file.available())
    {
      ch = file.read();
      if (ch == '\n')
      {
        return String(received);
      }
      received += ch;
    }
    return "";
  }

  void CloseFile()
  {
    if (file)
    {
      file.close();
      Serial.println("File closed");
    }
  }
 


  

};
