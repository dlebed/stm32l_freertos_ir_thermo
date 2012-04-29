#ifndef HD44780_H_
#define HD44780_H_

#include <stdint.h>

void initHD44780();
void freeHD44780();

void enableHD44780();
void disableHD44780();

void initHD44780GPIO();

void initHD44780ContrastPWM();
void stopHD44780ContrastPWM();


#endif /* HD44780_H_ */
