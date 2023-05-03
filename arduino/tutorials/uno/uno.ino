#include <SoftwareSerial.h>

#define BAUDRATE 9600
#define DEBUG true

SoftwareSerial esp8266(2, 3); // set the Rx ==> Pin 2; TX ==> Pin3.

int redLED = 13;

void setup()
{
  // put your setup code here, to run once:
  pinMode(redLED, OUTPUT);

  digitalWrite(redLED, HIGH);

  Serial.begin(BAUDRATE);   // begin hardware serial communication (0, 1) at specified BAUDRATE.
  esp8266.begin(BAUDRATE);  // begin software serial communication (2, 3) at specified BAUDRATE.
  InitWifiModule();         // initialize communication between ESP8266 and access point.
  
  digitalWrite(redLED, LOW);// after finishing the initialization successfully, turn off the LED (just an indicator).
}

// our main program, some fun are about to start
void loop()
{
  // put your main code here, to run repeatedly:

  if (esp8266.available())  // there's any data received and stored in the serial receive buffer.
  {
    if (esp8266.find("+IPD,")) // search for the "+IPD," string in the incoming data.
    {
      delay(1000);                                   // wait 1 second to fill up the buffer with the data.
      int connectionId = esp8266.read() - 48;        // Subtract 48 because the read() function returns the ASCII decimal value. And 0 (the first decimal number) starts at 48. We use it to convert from ASCI decimal value to a character value.
      esp8266.find("pin=");                          // Advance the cursor to the "pin=" part in the request header to read the incoming bytes after the "pin=" part which is the pinNumer and it's state.
      int pinNumber = (esp8266.read() - 48) * 10;    // read the first Byte from the Arduino input buffer(i.e. if the pin 12 then the 1st number is 1) then multiply this number by 10. So, the final value of the "pinNumber" variable will be 10.
      pinNumber = pinNumber + (esp8266.read() - 48); // read the second Byte from the Arduino input buffer(i.e. if the pin number is 12 then the 2nd number is 2) then add this number to the first number. So, the final value of the "pinNumber" variable will be 12.
      int statusLed = (esp8266.read() - 48);         // read the third byte from the Arduino input buffer. then save it inside the "statusLed" variable. At any case, it will be 1 or 0.
      digitalWrite(pinNumber, statusLed);            // then turn the LED at "pinNumber" on or off depending on the "statusLed" variable value.
      Serial.println(connectionId);                  // print the "connectionId" value on the serial monitor for debugging purposes.
      Serial.print(pinNumber);                       // print the "pinNumber" value on the serial monitor for debugging purposes.
      Serial.print("      ");                        // print some spaces on the serial monitor to make it more readable.
      Serial.println(statusLed);                     // print the "statusLed" value on the serial monitor for debugging purposes.
      String closeCommand = "AT+CIPCLOSE=";          // close the TCP/IP connection.
      closeCommand += connectionId;                  // append the "connectionId" value to the string.
      closeCommand += "\r\n";                        // append the "\r\n" to the string. it simulates the keyboard enter press.
      sendData(closeCommand, 1000, DEBUG);           // then send this command to the ESP8266 module to excute it.
    }
  }
}

/*
   Name: sendData

   Params: command - the AT Command to send to the ESP8266
                   - timeout - the time to wait for a response
                   - debug - print to Serial window?(true = yes, false = no)

   Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";               // initialize a String variable named "response". we will use it later.

  esp8266.print(command);             // send the AT command to the esp8266 (from ARDUINO to ESP8266).
  long int time = millis();           // get the operating time at this specific moment and save it inside the "time" variable.
  while ((time + timeout) > millis()) // excute only whitin 1 second.
  {
    while (esp8266.available())       // is there any response came from the ESP8266 and saved in the Arduino input buffer?
    {
      char c = esp8266.read();        // if yes, read the next character from the input buffer and save it in the "response" String variable.
      response += c;                  // append the next character to the response variabl. at the end we will get a string(array of characters) contains the response.
    }
  }
  if (debug)                          // if the "debug" variable value is TRUE, print the response on the Serial monitor.
  {
    Serial.print(response);
  }
  return response;                    // return the String response.
}

/*
   Name: InitWifiModule

   Params: Nothing.

   Returns: Nothing (void).
*/
void InitWifiModule()
{
  sendData("AT+RST\r\n", 3000, DEBUG); // reset the ESP8266 module.
  delay(3000);
  // sendData("AT+CWMODE=1\r\n", 1500, DEBUG); // set the ESP8266 WiFi mode to station mode.
  // delay(1000);
  // sendData("AT+CWJAP=\"PUT YOUR SSID\",\"PUT YOUR PASSWORD\"\r\n", 2000, DEBUG); // connect to the WiFi network.
  // delay(3000);
  sendData("AT+CIFSR\r\n", 1500, DEBUG); // Show IP Address, and the MAC Address.
  delay(1000);
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG); // Multiple conections.
  delay(1000);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG); // start the communication at port 80, port 80 used to communicate with the web servers through the http requests.
}
