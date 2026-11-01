#include"lcd_task.h"

//LCD pins
using lcd_rs = GpioE9;
using lcd_rw = GpioE11; //not used
using lcd_en = GpioE14;

using lcd_d4 = GpioE10;
using lcd_d5 = GpioE12;
using lcd_d6 = GpioE6;
using lcd_d7 = GpioE15;

/**  
* @brief: Constructor for LcdTask
*
* The Constructor calls rtos::Thread with a priority of 0 (low number = high priority)
* creates the connection to the TemperatureMonitoring-FSM
* and initiales the LCD
*
* @param: temperatureMonitoring: reference to TemperatureMonitoring-FSM
*/
LcdTask::LcdTask(TemperatureMonitoring& temperatureMonitoring):
	outpost::rtos::Thread(0),
	mTempMonitoring(temperatureMonitoring)
{
    lcd_init();
}


/**  
* @brief: run for LcdTask
*
* rtos::Threads require the virtual "run" function to be implemented.
* This function needs to contain an endless loop to be executed repeatedly.
* Depending on the state of the TemperatureMonitoring-FSM, the temperature is converted
* to the desired unit and displayed on the LCD.
* The LCD is renewed every 10 seconds.
*/
void LcdTask::run()
{
	while(true)
	{
		Board::Leds::write(0x00); //debug only
		lcd_clear(); //clear old value
		std::string str;
		int16_t temp = mTempMonitoring.getTemperature(); //temperature is given in Celsius

		switch (mTempMonitoring.getUnit())
		{
			case CELSIUS:
				str = std::to_string(temp) + " C";
				break;
			case KELVIN:
				temp = temp + 273; //conversion from Celsius to Kelvin
				str = std::to_string(temp) + " K";
				break;
			case FAHRENHEIT:
				temp = (temp * (9.0/5)) + 32; //conversion from Celsius to Fahrenheit
				str = std::to_string(temp) + " F";
				break;
			default:
				break;
		}

		lcd_send_string(str); //display string on LCD

		Board::Leds::write(0xFF); //debug only
		outpost::rtos::Thread::sleep(outpost::time::Seconds(10));
	}
}


/**  
* @brief: Sends data to the LCD
*
* Sends data to the LCD. RS is set to 1 for data and 0 for commands.
*
* @param: data: 8 bit of data to be sent
* @param: rs: output on the rs pin
*/
void LcdTask::send_to_lcd(char data, bool rs)
{
    lcd_rs::setOutput(rs);

	lcd_d7::setOutput(((data >> 3) & 0x01));
	lcd_d6::setOutput(((data >> 2) & 0x01));
	lcd_d5::setOutput(((data >> 1) & 0x01));
	lcd_d4::setOutput(((data >> 0) & 0x01));

	lcd_en::setOutput(true);
	modm::delay(ENABLE_DELAY);
	lcd_en::setOutput(false);
	modm::delay(ENABLE_DELAY);
}


/**
* @brief: Initializes the LCD
 */
void LcdTask::lcd_init(void)
{
    modm::delay(50ms); //wait 15ms or more after startup
	send_to_lcd(0x03, false); //see https://hades.mech.northwestern.edu/images/f/f7/LCD16x2_HJ1602A.pdf, p. 6 for commands and delays
	modm::delay(5ms); //wait 4.1ms or more
	send_to_lcd(0x03, false);
	modm::delay(5ms); //wait 100us or more
	send_to_lcd(0x03, false);
	modm::delay(5ms); //third go: not clear from datasheet why it's necessary, but will not work without three tries
	send_to_lcd(0x02, false); //set 4b bit mode
	modm::delay(10ms); //experimental

	lcd_send_cmd(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x7 characters)
	modm::delay(50us); //40us wait for Function Set to complete
	lcd_send_cmd(0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	modm::delay(50us); //40us wait for Display Off to complete
	lcd_send_cmd(0x01);  // clear display
	modm::delay(2ms); //1.61ms wait for Display Clear to complete
	lcd_send_cmd(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	modm::delay(50us); //40us wait for Entry Mode Set to complete
	lcd_send_cmd(0x0C); //Display on/off control --> D = 1 for Display ON, C and B = 0. (Cursor off and blink off)
	modm::delay(50us); //40us wait for Display On to complete
}


/**  
* @brief: Sends Command to the LCD
*/
void LcdTask::lcd_send_cmd(char cmd)
{
    char datatosend;

    /* send upper nibble first */
    datatosend = ((cmd>>4)&0x0F);
    send_to_lcd(datatosend, false);  // RS must be 0 while sending command

    /* send Lower Nibble */
    datatosend = ((cmd)&0x0F);
	send_to_lcd(datatosend, false);
}


/**  
* @brief: Sends Data to the LCD
*/
void LcdTask::lcd_send_data(char data)
{
    char datatosend;

	/* send higher nibble */
	datatosend = ((data>>4)&0x0F);
	send_to_lcd(datatosend, true);  // rs =1 for sending data

	/* send Lower nibble */
	datatosend = ((data)&0x0F);
	send_to_lcd(datatosend, true);
}

/**  
* @brief: Sends String to the LCD
*/
void LcdTask::lcd_send_string (std::string str)
{
	int strlen = str.length();

	int i;
	for(i = 0; i<strlen; i++)
	{
		lcd_send_data(str[i]); //cursor will be automatically incremented after each byte sent
	}
}

/**  
* @brief: Sends String to the LCD
*
* Puts cursor to the specified position on the LCD. This is where the next character will be displayed.
*
* @param: row: row the cursor is to be placed at (0 or 1)
* @param: col: column the cursor is to be placed at (0-15)
*/
void LcdTask::lcd_put_cur(int row, int col)
{
	switch (row)
    {
        case 0:	//upper row
            col |= 0x80;
            break;
        case 1: //lower row
            col |= 0xC0;
            break;
		default:
			break;
    }

    lcd_send_cmd(col);
}


/**  
* @brief: Clears entire LCD
*/
void LcdTask::lcd_clear(void)
{
	lcd_send_cmd(0x01);
	modm::delay(2ms); //1.61ms minimum wait for Display Clear to complete
}