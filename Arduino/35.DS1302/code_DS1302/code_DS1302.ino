

/**
* @par Copyright (C): 2010-2019, Shenzhen Yahboom Tech
* @file         35.DS1302 Serial port display time
* @author      liusen
* @version      V1.0
* @date         2017.11.14
* @brief        Arduino connect to DS1302
                Serial input: 2017,11,10,11,59,20,6   
                Note:     1-7 Sunday - Saturday
* @details
* @par History  
*
*/

#include <stdio.h>
#include <string.h>
#include <DS1302.h>

uint8_t CE_PIN   = 5;
uint8_t IO_PIN   = 6;
uint8_t SCLK_PIN = 7;


char buf[50];
char day[10];
String comdata = "";
int numdata[7] ={0}, j = 0, mark = 0;

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);

/**
* Function       print_time
* @author        liusen
* @date          2017.11.14
* @brief         Serial printing time
* @param[in]     void
* @retval        void
* @par History   
*/
void print_time()
{
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
    Serial.begin(9600);   
    rtc.write_protect(false);//turn off write protection
    rtc.halt(false);       
}
/**
* Function       loop
* @author        liusen
* @date          2017.11.14
* @brief         Serial port timing and display
* @param[in]     void
* @retval        void
* @par History   
*/
void loop()
{
    while (Serial.available() > 0)
    {
        comdata += char(Serial.read()); 
        delay(2);
        mark = 1;
    }
    if(mark == 1) 
    {
        Serial.print("You inputed : "); 
        Serial.println(comdata); 
        for(int i = 0; i < comdata.length() ; i++)
        {
            if(comdata[i] == ',' || comdata[i] == 0x10 || comdata[i] == 0x13)
            {
                j++;
            }
            else
            {
                numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
            }
        }
        Time t(numdata[0], numdata[1], numdata[2], numdata[3], numdata[4], numdata[5], numdata[6]);
        rtc.time(t); 
        mark = 0;j=0;
        comdata = String("");
        for(int i = 0; i < 7 ; i++) numdata[i]=0;
    }
    print_time();
    delay(1000);
}
