/*
 * Authors: Janina
 * LCD functions: https://controllerstech.com/interface-lcd-16x2-with-stm32-without-i2c/ (modified by Janina)
*/

#ifndef LCD_TASK_H
#define LCD_TASK_H

#include<cstdint>

#include <outpost/rtos.h>
#include <outpost/rtos/thread.h>

#include <modm/board.hpp>
#include <modm/debug/logger.hpp>

#include"temperature_monitoring.h"

#define ENABLE_DELAY 50us


class LcdTask : public outpost::rtos::Thread
{
    public:
    LcdTask(TemperatureMonitoring& temperatureMonitoring);

    ~LcdTask() = default;

    void run();

    private:

    TemperatureMonitoring& mTempMonitoring;

    void send_to_lcd(char data, bool rs);
    void lcd_init(void);   // initialize lcd
    void lcd_send_cmd(char cmd);  // send command to the lcd
    void lcd_send_data(char data);  // send data to the lcd
    void lcd_send_string(std::string str);  // send string to the lcd
    void lcd_put_cur(int row, int col);  // put cursor at the entered position row (0 or 1), col (0-15);
    void lcd_clear(void);
};

#endif