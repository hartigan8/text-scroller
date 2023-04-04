// C++ code
//
#include <LiquidCrystal_I2C.h>
boolean SCROLL_FLAG = true;
int SCROLL_WAIT = 1000;
char SCROLL_DIRECTION = 'L';
char LCD_ROW_1 [] = "This text is for row 0 and longer than 16 characters.";
char LCD_ROW_2 [] = "ABCD EFGH";



LiquidCrystal_I2C lcd (32, 16, 2);

int text1Len;
int text2Len;
int c1 = 0;
int c2 = 0;

void setup()
{
  delay(10);
  lcd.init();
  Serial.begin(9600);
  text1Len = strlen(LCD_ROW_1);
  text2Len = strlen(LCD_ROW_2);
}

void loop()
{
  
  printScreen(text1Len, c1, 0, LCD_ROW_1);
  printScreen(text2Len, c2, 1, LCD_ROW_2);
  if(SCROLL_FLAG){
    if(SCROLL_DIRECTION == 'L'){
      c1++;
      c2++;
      c1 = c1 % (text1Len * 16);
      c2 = c2 % (text2Len * 16);
    }
    else if(SCROLL_DIRECTION == 'R'){
      c1--;
      c2--;

      c1 = (c1%(text1Len * 16) + (text1Len * 16))%(text1Len * 16);
      c2 = (c2%(text2Len * 16) + (text2Len * 16))%(text2Len * 16);
    }
  }
  
  delay(SCROLL_WAIT);
  lcd.clear();
  
}

void printScreen(int textLen, int counter, int row, char text[])
{
  for(int i = 0; i < 16; i++){
    int charIndex = i + counter;
    
    lcd.setCursor(i, row);
    
    if(text[charIndex] != '\0' && charIndex <= textLen)
    {
     
      lcd.print(text[charIndex]); 
    }
    else if(charIndex % 16 >= textLen);
    else if(textLen < 16)
    {
      lcd.print(text[charIndex % 16 % textLen]);
    }
    else lcd.print(text[charIndex % textLen]);
  }
}
