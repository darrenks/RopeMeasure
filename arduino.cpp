//source for rotary encoder http://www.circuitsathome.com/mcu/programming/reading-rotary-encoder-on-arduino

int i=0;

//void setup() {
//  Serial.begin(9600);
//  //pinMode(11, OUTPUT);
//}

//write a number
static int last_number=10000;
void writeNumber(int number) {
  if(number==last_number) return;
  last_number=number;
  Serial.write(0x76); //reset the display
  
  //set brightness
  Serial.write(0x7a);
  Serial.write(0x01);
  
  // write decimal point
  //Serial.write(0x77);
  //Serial.write(0x04);
  
  if(number<0) number=-number;
  number%=10000;
  
  Serial.print(number/1000);
  number%=1000;
  Serial.print(number/100);
  number%=100;
  Serial.print(number/10);
  number%=10;
  Serial.print(number);
}

//void loop() {
//  writeNumber(i);
//  i+=1;
//  delay(10);
//}

/* Rotary encoder read example */
#define ENC_A A0
#define ENC_B A1
#define ENC_PORT PINC
 
void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  Serial.begin(9600);
  pinMode(A5, OUTPUT);
  analogWrite(A5, 512);
  pinMode(8, OUTPUT);
  
  writeNumber(0);
}
 
void loop()
{
// digitalWrite(8, LOW);
// digitalWrite(8, HIGH);
 static int counter = 0;      //this variable will be changed by encoder input
 int8_t tmpdata;
 /**/
  tmpdata = read_encoder();
  if( tmpdata ) {
    //Serial.print("Counter value: ");
    //Serial.println(counter, DEC);
    writeNumber(counter/(350*12));
    counter += tmpdata;
  }
}
 
/* returns change in encoder state (-1,0,1) */
int8_t read_encoder()
{
  static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t old_AB = 0;
  /**/
  old_AB <<= 2;                   //remember previous state
  old_AB |= ( ENC_PORT & 0x03 );  //add current state
  return ( enc_states[( old_AB & 0x0f )]);
}