#define LED 13
#define BAUDRATE 115200
#define DEBUGOUTPUT 0
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;
long lastReceivedPacket = 0;
boolean bigPacket = false;

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode (8,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode (10,OUTPUT);
  pinMode(11, OUTPUT);
  
  
  Serial.begin(57600);
}

byte ReadOneByte()
{
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();

#if DEBUGOUTPUT  
  Serial.print((char)ByteRead);
#endif
  return ByteRead;
}
void loop()
{
  if(ReadOneByte() == 170) {
    if(ReadOneByte() == 170) {
      payloadLength = ReadOneByte();
      if(payloadLength > 169)  
          return;

      generatedChecksum = 0;        
      for(int i = 0; i < payloadLength; i++)
      {  
        payloadData[i] = ReadOneByte(); 
        generatedChecksum += payloadData[i];
      }   

      checksum = ReadOneByte();         
      generatedChecksum = 255 - generatedChecksum; 

        if(checksum == generatedChecksum)
        {    
        poorQuality = 200;
        attention = 0;
        meditation = 0;

        for(int i = 0; i < payloadLength; i++) 
        {  
          switch (payloadData[i]) {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4:
            i++;
            attention = payloadData[i];                        
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:
            i = i + 25;      
            break;
          default:
            break;
          } // switch
        } // for loop

#if !DEBUGOUTPUT
        if(bigPacket)
        {
          Serial.print("PoorQuality: ");
          Serial.print(poorQuality, DEC);
          Serial.print(" Attention: ");
          Serial.print(attention, DEC);
          Serial.print(" Meditation: ");
          Serial.print(meditation, DEC);
          if(attention > 50)
           { digitalWrite(13,HIGH);
           digitalWrite (8, HIGH);
           digitalWrite (9, LOW);
           digitalWrite (10, HIGH);
           digitalWrite (11, LOW);
           
        
           }
          else
          {
            digitalWrite(13,LOW);
            digitalWrite (8, LOW);
           digitalWrite (9, LOW);
           digitalWrite (10, LOW);
           digitalWrite (11, LOW);
          }
          Serial.print(" Time since last packet: ");
          Serial.print(millis() - lastReceivedPacket, DEC);
          lastReceivedPacket = millis();
          Serial.print("\n");
        }
#endif        
        bigPacket = false;        
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
}
