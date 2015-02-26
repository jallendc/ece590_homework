//code edited from inclass code used

byte index = 0;
char inChar; // Where to store the character read

void setup() {
  pinMode(BOARD_LED_PIN, OUTPUT);
  Serial1.begin(9600);
}

void loop() {
  if(Serial1.available() > 0)
  {
    char inData[20];
    while(Serial1.available() > 0)
    {  
      if(index < 19)
      {
        inChar = Serial1.read();
        inData[index] = inChar;
        index++;
        inData[index] = '\0'; //Null terminate the string
      }
    }
    index = 0;
    Serial1.print("ret: ");
    Serial1.println(inData);
    Serial1.println(13);
    Serial1.println(10);
    
    if(inData[0] == 97){
      
      for(int i=0; i<100; i++){
        toggleLED();
        delay(100);
      }
    }
  }
  delay(20);
}
