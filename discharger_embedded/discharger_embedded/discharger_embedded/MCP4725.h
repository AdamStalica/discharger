/* 
* MCP4725.h
*
* Created: 15.10.2019 10:31:32
* Author: domin
*/


#ifndef __MCP4725_H__
#define __MCP4725_H__

#define DEVICE_CODE 0xC0
#define MPC4725_A2 0
#define MPC4725_A1 0
#define MPC4725_A0 0
#define DEVICE_ADDRESS (DEVICE_CODE | (MPC4725_A2 << 3) | (MPC4725_A1 << 2) | (MPC4725_A0 << 1))

/*
*	WRITE COMMANDS TYPE
*	C0	|	Type
*	-----------------------------------------------
*	0	|	Write DAC Register
*	1	|	Write DAC Register and EEPROM
*/
#define MPC4725_C2 0
#define MPC4725_C1 1
#define MPC4725_C0 0
#define WRITE_COMMAND_TYPE ((MPC4725_C2 << 7) | (MPC4725_C1 << 6) | (MPC4725_C0 << 5))

/*
*	POWER-DOWN BITS
*	PD1	|	PD0	|	Function
*	-----------------------------------------------
*	0	|	0	|	Normal mode
*	0	|	1	|	1kOhm resistor to the ground
*	1	|	0	|	100kOhm resistor to the ground
*	1	|	1	|	500kOhm resistor to the ground
*/
#define MPC4725_PD1 0
#define MPC4725_PD0 0
#define POWER_DOWN_BITS ((MPC4725_PD1 << 2) | (MPC4725_PD0 << 1))

#define DATA_WRITE_FIRST_BYTE (WRITE_COMMAND_TYPE | POWER_DOWN_BITS)

#include "I2CMaster.h"

class MCP4725 : public I2CMaster
{
	
//functions
public:
	MCP4725(unsigned long fCpu);
	~MCP4725();
	uint8_t readData(uint8_t * tab, uint8_t size);
	uint8_t writeDACData(uint16_t dacValue);
	
private:
	MCP4725( const MCP4725 &c );
	MCP4725& operator=( const MCP4725 &c );

}; //MCP4725

#endif //__MCP4725_H__
