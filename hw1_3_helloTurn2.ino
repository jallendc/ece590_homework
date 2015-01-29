/* hw1_3_helloTurn
 
 modified from Dynamixel Basic Position Control Example
 
 b_setID program used to set the ID of servo from 1 to 2.
 
 Sets the position of servo 1 to 45 degrees then sets the position to 90 degrees repeatedly with a 0.5Hz cycle.
 Sets the position of servo 2 to 0 degrees then sets the position to 180 degrees repeatedly with a 1.0Hz cycle.
 
                   Compatibility
 CM900                  O
 OpenCM9.04             O
 
                  Dynamixel Compatibility
               AX    MX      RX    XL-320    Pro
 CM900          O      O      O        O      X
 OpenCM9.04     O      O      O        O      X
 **** OpenCM 485 EXP board is needed to use 4 pin Dynamixel and Pro Series ****
 
 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */
/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define ID_NUM1 1
#define ID_NUM2 2
/* Control table defines */
#define GOAL_POSITION 30

Dynamixel Dxl(DXL_BUS_SERIAL1);

void setup() {
  
  // Dynamixel 2.0 Baudrate -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  //Dxl.setID(2, NEW_ID); //Dynamixel_ID_Change 1 to 2
  Dxl.jointMode(ID_NUM1); //jointMode() is to use position mode
  Dxl.jointMode(ID_NUM2); //jointMode() is to use position mode
}

void loop() {  
  //Turn dynamixel ID 2 to 0 degrees  
  Dxl.writeWord(ID_NUM2, GOAL_POSITION, 0);
  delay(500); // 0.5 seconds
  //Turn dynamixel ID 1 to 45 degrees, ID 2 to 180 degrees
  Dxl.writeWord(ID_NUM1, GOAL_POSITION, 307);
  Dxl.writeWord(ID_NUM2, GOAL_POSITION, 614);
  delay(500); // 1 second

  //Turn dynamixel ID 2 to 0 degrees  
  Dxl.writeWord(ID_NUM2, GOAL_POSITION, 0);
  delay(500); // 1.5 seconds
  //Turn dynamixel ID 1 to 90 degrees, ID 2 to 180 degrees
  Dxl.writeWord(ID_NUM1, GOAL_POSITION, 153);
  Dxl.writeWord(ID_NUM2, GOAL_POSITION, 614);
  delay(500); // 2 seconds
}


