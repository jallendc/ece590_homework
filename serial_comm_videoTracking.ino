#define DXL_BUS_SERIAL1 1 //Dynamixel on Serial1(USART1) <-OpenCM9.04 
#define DXL_BUS_SERIAL2 3 //Dynamixel on Serial2(USART2) <-LN101,BT210 
#define DXL_BUS_SERIAL3 3 //Dynamixel on Serial3(USART3) <-OpenCM 485EXP

Dynamixel Dxl(DXL_BUS_SERIAL1);

byte index = 0;
char inChar; // Where to store the character read
int sig;
int mag;
int wheelSpeed;
int scale = 40;

void setup() 
{
  //pinMode(BOARD_LED_PIN, OUTPUT);
  //Serial1.begin(9600);
  Dxl.begin(3);
  Dxl.wheelMode(2);
  Serial2.begin(9600);
}

void loop() 
{
  if(Serial2.available() > 0)
  {
    char inData[20];
    while(Serial2.available() > 0)
    {  
      if(index < 19)
      {
        inChar = Serial2.read(); // read a character
        inData[index] = inChar;
        index++;
        inData[index] = '\0'; // Null terminate the string
      }
    }
    
    index = 0;
    sig = atoi(inData);
    mag = atoi(inData);
    sig = byte(sig) & 0x80;
    //SerialUSB.println(sig);
    if (sig >0)
    {
      sig = 255; 
    }
    else sig = 1; 
    mag = byte(mag) & 0x7F;
    //mag = mag + 1025;
    byte val = sig*mag;
    //SerialUSB.println(sig);
    //SerialUSB.println(mag);
    //SerialUSB.println(val);
    
    if(sig == 255)
    {
      wheelSpeed = mag*scale + 1024;
    }
        
    else  wheelSpeed = mag*scale;
    
    wheelSpeed = int(wheelSpeed);
    
    SerialUSB.println(wheelSpeed);
    
    if (wheelSpeed > 0)
    {
      Dxl.goalSpeed(2, wheelSpeed);
      delay(20);
      Dxl.goalSpeed(2, 0);
    }
    
    else
    {
      Dxl.goalSpeed(2, 0);
      delay(100);
    }   
    
    
//    if (inData[index-1] == 13)
//    {
//    index = 0;
//    sig = 0;
//    //SerialUSB.write(inData,3);
    //sig = int(inData);
//    SerialUSB.println(sig);
    //SerialUSB.write(sig);
    //moveMotor();
//    }
  }
  delay(20);
}

//void moveMotor(float inFloat)
//{
  
//}

