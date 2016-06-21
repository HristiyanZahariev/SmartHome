#define DEBUG true

void setup()
{
  Serial.begin(9600);
  Serial1.begin(115200);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  sendData("AT+RST\r\n",2000,DEBUG);
  sendData("AT+CWJAP=\"Network 72\",\"\"\r\n",10000,DEBUG); 
  sendData("AT+CIFSR\r\n",1000,DEBUG);
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
}

void loop()
{
  if(Serial1.available()) 
  {
 
    
    if(Serial1.find("+IPD,"))
    {
     delay(1000); 
     int connectionId = Serial1.read()-48; 
          
     Serial1.find("pin="); 
     
     int pinNumber = (Serial1.read()-48)*10;
     pinNumber += (Serial1.read()-48);
     
     digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin   
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId;
     closeCommand+="\r\n";
     sendData(closeCommand,1000,DEBUG);
    }
  }
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command);
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial1.available())
      {
        char c = Serial1.read();
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}