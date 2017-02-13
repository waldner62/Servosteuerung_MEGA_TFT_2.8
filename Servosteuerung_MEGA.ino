/*
   Small Program to control servos using a 2.8" TFT Touchscreen
   Program does not act as an USB HID Device, for reference purposes only
   Tested on Arduino MEGA Only and 0x9341
   By waldner62

   Note:
  
   Open the Serial Monitor to see the program running
   Enjoy!
*/
#include <Servo.h> 
Servo myservo_0;int pos = 0;Servo myservo_1;
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include <Adafruit_TFTLCD.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

// calibration mins and max for raw data when touching edges of screen
// YOU CAN USE THIS SKETCH TO DETERMINE THE RAW X AND Y OF THE EDGES TO GET YOUR HIGHS AND LOWS FOR X AND Y
#define TS_MINX 120
#define TS_MINY 20
#define TS_MAXX 900
#define TS_MAXY 940

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

//Color Definitons
#define BLACK     0x0000
#define BLUE      0x001F
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define MINPRESSURE 1
#define MAXPRESSURE 1000



// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
// Pins A2-A6
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

//Size of key containers 70px
#define BOXSIZE 70



Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Container variables for touch coordinates
int X, Y, Z;

//Screen height without hidden pixel
double tHeight = tft.height() - 1;
//Centering the mid square
double center = (tft.width() / 2) - (BOXSIZE / 2);
//Space between squares
double padding = 8;
//Position of squares to the left and right of center
double fromCenter = BOXSIZE + padding;
//Second row Y-Axis position
double secondRow = BOXSIZE + padding;
//Third row Y-Axis position
double thirdRow = secondRow + BOXSIZE + padding;
//Fourth row Y-Axis position
double fourthRow = thirdRow + BOXSIZE + padding;
//Y-Axis align for all squares
double verticalAlign = (tHeight - ((BOXSIZE * 4) + (padding * 3))) / 2;
//Left column starting x posision
double leftColPositionX = center - fromCenter;
//Mid column starting x posision
double midColPositionX = center;
//Right column starting x posision
double rightColPositionX = center + fromCenter;

void setup() {tft.setRotation(0);
{ 
  myservo_0.attach(53);  // attaches the servo on pin 9 to the servo object 
  myservo_1.attach(52);
} 
  Serial.begin(9600);

  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(0x9341);
tft.setRotation(0);
  //Background color
  tft.fillScreen(LIGHTGREY);

  // draw num pad
  createButtons();
  insertNumbers();
  Serial.println(F("Press any button on the TFT screen: "));



}

void loop() {

tft.setRotation(0);
  retrieveTouch();
  int boxHeightRow1 = verticalAlign + BOXSIZE;
  int boxHeightRow2 = secondRow + BOXSIZE;
  int boxHeightRow3 = thirdRow + BOXSIZE;
  int boxHeightRow4 = fourthRow + BOXSIZE;

  if (Z > MINPRESSURE && Z < MAXPRESSURE) {

    //redraw numpad to clear old number
    tft.fillScreen(LIGHTGREY);
    createButtons();
    insertNumbers();
    //default text setup for number display on tft
    tft.setCursor(100, 120);
    tft.setTextColor(RED);
    tft.setTextSize(5);

    //Check if element clicked is in left column
    if (X > leftColPositionX && X < (leftColPositionX + BOXSIZE))
   
    {
      //Check if element clicked is in row 1
      
      if (Y > verticalAlign) {
        double midColCursorX    = midColPositionX  + (BOXSIZE / 3);
         double firstRowCursorY  = verticalAlign + (BOXSIZE / 3);
        if (Y < boxHeightRow1) 
        
        {double leftColCursorX   = leftColPositionX + (BOXSIZE / 3);double firstRowCursorY  = verticalAlign + (BOXSIZE / 3);
          Serial.println("1 Servo 0");tft.fillScreen(BLUE);tft.drawRect(leftColPositionX, verticalAlign, BOXSIZE*3+2*padding, BOXSIZE, BLACK);
          tft.fillRect(leftColPositionX, verticalAlign, BOXSIZE*3+2*padding, BOXSIZE, RED);
          tft.setCursor(leftColCursorX, firstRowCursorY);tft.setTextSize(4);
  tft.setTextColor(BLACK);
  tft.setCursor(X = 45, firstRowCursorY);

          tft.println("Servo 0"); delay(150);
           { 
  for(pos = 0; pos < 180; pos += 20)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 20 degree 
    myservo_0.write(pos); Serial.println(pos);             // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo_0.write(pos); Serial.println(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} tft.fillScreen(LIGHTGREY); createButtons();
  insertNumbers();
        
        }
       
      }
      //Check if element clicked is in mid column
    } else if (X > midColPositionX && X < (midColPositionX + BOXSIZE)) {
      //Check if element clicked is in row 1
      if (Y > verticalAlign) {
        if (Y < boxHeightRow1) {
          Serial.println("2 Servo 1");
          tft.println("2");
          delay(150);
           { 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo_1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=20)     // goes from 180 degrees to 0 degrees 20 degrees
  {                                
    myservo_1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
         
        }
       
       
        
      }
      //Check if element clicked is in third column
    } else if (X > rightColPositionX && X < (rightColPositionX + BOXSIZE)) {
      if (Y > verticalAlign) {
        //Check if element clicked is in row 1
        if (Y < boxHeightRow1) {
           tft.setCursor(50, 120);
    tft.setTextColor(RED);
    tft.setTextSize(5);
          Serial.println("3 Servo 0 + 1");
          tft.println("1 + 2");
          delay(150);
           { 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo_1.write(pos); myservo_0.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo_1.write(pos);myservo_0.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
} 
        }
       
       
      
      }
    }

    // good for debuggin, prints out the x,y cordinates of the press
    // tft.setTextSize(3);
    // tft.print("X = "); tft.println(X);
    // tft.print("Y = "); tft.println(Y);
     Serial.print("X= ");Serial.println(X);Serial.print("Y= ");Serial.println(Y);
  }
}

void retrieveTouch()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  //If sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);




 
  X = tft.width() - map(p.x, TS_MAXX, TS_MINX, 0, tft.width());
  Y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());
  Z = p.z;



}

void createButtons() {
  //(initial x,initial y,width,height,color)
  double secondRowVertialAlign = secondRow + verticalAlign;
  double thirdRowVertialAlign = thirdRow + verticalAlign;
  double fourthRowVertialAlign = fourthRow + verticalAlign;

  /***Draw filled squares with specified dimensions and position***/
  //First Row
  tft.fillRect(leftColPositionX, verticalAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(midColPositionX, verticalAlign, BOXSIZE, BOXSIZE, GREEN);
  tft.fillRect(rightColPositionX, verticalAlign, BOXSIZE/2, BOXSIZE, RED);
  tft.fillRect(rightColPositionX+35, verticalAlign, BOXSIZE/2, BOXSIZE, GREEN);
  //Second Row
  tft.fillRect(leftColPositionX, secondRowVertialAlign, BOXSIZE*3+2*padding, BOXSIZE, BLUE);
 

  //Third Row
  tft.fillRect(leftColPositionX, thirdRowVertialAlign, BOXSIZE*3+2*padding, BOXSIZE, BLUE);
  

  //Fourth Row
  tft.fillRect(leftColPositionX, fourthRowVertialAlign, BOXSIZE*3+2*padding, BOXSIZE, BLUE);
 

  /***Draw Borders around squares***/
  //First Row
  tft.drawRect(leftColPositionX, verticalAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(midColPositionX, verticalAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(rightColPositionX, verticalAlign, BOXSIZE, BOXSIZE, BLACK);

  //Second Row
  tft.drawRect(leftColPositionX, secondRowVertialAlign, BOXSIZE*3+2*padding, BOXSIZE, BLACK);
  

  //Third Row
  tft.drawRect(leftColPositionX, thirdRowVertialAlign, BOXSIZE*3+2*padding, BOXSIZE, BLACK);
  

  //Fourth Row
  tft.drawRect(leftColPositionX, fourthRowVertialAlign, BOXSIZE *3+2*padding, BOXSIZE, BLACK);
  
}

void insertNumbers() {
  //Centers text horizontally on all three columns
  double leftColCursorX   = leftColPositionX + (BOXSIZE / 3);
  double midColCursorX    = midColPositionX  + (BOXSIZE / 3);
  double rightColCursorX  = rightColPositionX + (BOXSIZE / 3);
  //Centers text horizontally on all four rows
  double firstRowCursorY  = verticalAlign + (BOXSIZE / 3);
  double secondRowCursorY = secondRow + firstRowCursorY;
  double thirdRowCursorY  = thirdRow  + firstRowCursorY;
  double fourthRowCursorY = fourthRow + firstRowCursorY;

  tft.setTextSize(4);
  tft.setTextColor(BLACK);

  
  tft.setCursor(leftColCursorX, firstRowCursorY);
  tft.println("1");

  tft.setCursor(midColCursorX, firstRowCursorY);
  tft.println("2");

  
  tft.setCursor(rightColCursorX-10, firstRowCursorY);
  tft.println("12");

  
   tft.setTextSize(2.9);
  tft.setCursor(leftColCursorX, secondRowCursorY);
  tft.println("Servosteuerung");

 
  
  tft.setCursor(leftColCursorX+70, thirdRowCursorY);
  tft.println("von");

  

 
  tft.setCursor(leftColPositionX + 55, fourthRowCursorY);
  tft.println("waldner62");


}




