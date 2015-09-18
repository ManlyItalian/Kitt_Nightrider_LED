// Name:Zachary Carofanello
// Date: 09/15/2015
// Class: CPET 202
// Project Name:Nightrider LED display
// Description: Has a shift register count up to 10 then back down
//              to 0 to create a kit night rider effect
// Version: 0.9
//
//			  LED Bar naming scheme
//		 ██ ██ ██ ██ ██ ██ ██ ██ ██ ██
// LED # 0  1  2  3  4  5  6  7  8  9
// Pin   Q0 Q1 Q2 Q3 Q4 Q5 Q6 Q7 SD CLK
// SD: Serial Data, CLK: Serial Clock, Q: Shift Register Output
//
// Pin 12 = Serial Data  = PORTB bit 4
// Pin 13 = Serial Clock = PORTB bit 5
//

#define LED_SPEED 3

//Sends a number of low bits through the register to clear the outputs
void ClearShiftRegister(int NumClear){
  for(int i=0;i<NumClear;i++){
  PORTB |= 0x20;      //Setting Clock High
  PORTB &= 0xDF;      //Setting Clock Low
  }
}

//Pushes a bit down to the desired LED and holding it for the pause desired
void GoToNum(int num, int pause){
  
  PORTB |= 0x10;        //Set Serial Data
  PORTB |= 0x20;        //Set Clock
  PORTB &= 0xCF;        //Clear Clock and Data
  
  for(int i=0;i<=num;i++){
  //LED 8 is the data LED
  if(i == 8){
    PORTB |= 0x10;     //Set Serial Data
    delay(pause);
    PORTB ^= 0x10;     //Clear Serial Data
  }
  //LED 9 is the clock LED
  else if(i == 9){
    PORTB |= 0x20;    //Set Serial Clock
    delay(pause);
    PORTB ^= 0x20;    //Clear Serial Clock
  }
  //Pauses on the desired LED
  else if(i == num){
    delay(pause);
  }
  //If the desired LED isn't reached then send it one more down
  else{
    PORTB |= 0x20;      //Set Clock
    PORTB ^= 0x20;      //Clear Clock
  }
  }
  ClearShiftRegister(8-num);
  //Debugging purposes
  Serial.println(num);
}

void setup(){ 
  DDRB |= 0x30;           //Set bits 12 and 13
  PORTB &= 0xCF;          //Clear Clock and Data
  
  //Making sure there isn't any data in the register
  ClearShiftRegister(8);

  //Debugging
  Serial.begin(9600);
  Serial.println(F("Lab #3: Shift Registers v1.0"));
}

void loop(){
//Counts up to LED 9
for(int i=0;i<10;i++)
  GoToNum(i, LED_SPEED);

//Counts down to LED 0
for(int i=8;i>=0;i--)
  GoToNum(i, LED_SPEED);

Serial.println(F("DONE!"));
}

/*
//Sends 8 high bits through the register to set all the outputs high
void TurnOnAll(){
  PORTB |= 0x10;			//Setting Serial Data
  for(int i = 0;i<8;i++){
    PORTB |= 0x20;			//Setting Clock High
    PORTB &= 0xDF;			//Setting Clock Low
  }
  PORTB |= 0x20;			//Setting Serial Clock High
}
*/
