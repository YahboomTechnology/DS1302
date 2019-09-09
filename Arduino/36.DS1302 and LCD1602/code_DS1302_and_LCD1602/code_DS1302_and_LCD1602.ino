/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         36.DS1302 and LCD1602
* @author       liusen
* @version      V1.0
* @date         2017.11.14
* @brief        Arduino Sensor Kit
* @details      Arduino connect to DS1302
                Serial input: 2017,11,10,11,59,20,6   
                Note:     1-7 Sunday - Saturday
* @par History  
*
*/

#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include <LiquidCrystal.h>

const uint8_t CE_PIN   = A3;
const uint8_t IO_PIN   = A4;
const uint8_t SCLK_PIN = A5;

char day[10];
int numdata[7] ={0};
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
LiquidCrystal lcd(12,11,10,5,4,3,2);
/**
* Function       print_time
* @author        liusen
* @date          2017.11.14
* @brief         Print time to serial port
* @param[in]     void
* @retval        void
* @par History   
*/
void print_time()
{
    char buf[30];
    Time t = rtc.time();
    memset(day, 0, sizeof(day));
    switch (t.day)
    {
    case 1: strcpy(day, "Sunday"); break;
    case 2: strcpy(day, "Monday"); break;
    case 3: strcpy(day, "Tuesday"); break;
    case 4: strcpy(day, "Wednesday"); break;
    case 5: strcpy(day, "Thursday"); break;
    case 6: strcpy(day, "Friday"); break;
    case 7: strcpy(day, "Saturday"); break;
    }
    snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d", day, t.yr, t.mon, t.date, t.hr, t.min, t.sec);
    Serial.println(buf);
}

/**
* Function       print_time
* @author        liusen
* @date          2017.11.14
* @brief         LCD1602 display
* @param[in]     void
* @retval        void
* @par History   
*/
void display_time()
{
    char  temp[30] = {0};
    Time t = rtc.time();
    char week[5];
    switch (t.day)
    {
      case 1:  strcpy(week , "Sun"); break;
      case 2:  strcpy(week ,"Mon"); break;
      case 3:  strcpy(week ,"Tues"); break;
      case 4:  strcpy(week ,"Wed"); break;
      case 5:  strcpy(week ,"Thur"); break;
      case 6:  strcpy(week ,"Fri"); break;
      case 7:  strcpy(week ,"Sat"); break;
    }
    
    snprintf(temp, sizeof(temp), "%02d-%02d-%02d %s", t.yr, t.mon, t.date, week); //t.yr, t.mon, t.date, t.hr, t.min, t.sec ,week
    lcd.setCursor(1,0);
    lcd.print(temp);
    snprintf(temp, sizeof(temp), "%02d:%02d:%02d", t.hr, t.min, t.sec );
    lcd.setCursor(4,1);
    lcd.print(temp);
}
/**
* Function       setup
* @author        liusen
* @date          2017.11.14
* @brief         Initialization configure
* @param[in]     void
* @retval        void
* @par History   
*/
void setup()
{
   
    Serial.begin(9600);   //The baud rate is 9600
    rtc.write_protect(false);  //turn off write protection
    rtc.halt(false);   
    
    lcd.begin(16, 2); //Define 1602 liquid crystal display range is 2 rows and 16 columns of characters
    lcd.home();//Move the cursor back to the upper left corner, that is, output from the beginning
    lcd.clear(); 
    
    Time t(2017, 11, 25, 18, 39, 25, 7);  
    rtc.time(t);  
    rtc.write_protect(true); // turn on write protection
    
}
/**
* Function       loop
* @author        liusen
* @date          2017.11.14
* @brief         Print and display the current time
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
    print_time();
    display_time();
    delay(1000);
}



