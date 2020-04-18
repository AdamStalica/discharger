/* 
* StringProcessor.h
*
* Created: 18.04.2020 17:20:07
* Author: domin
*/


#ifndef __STRINGPROCESSOR_H__
#define __STRINGPROCESSOR_H__

#include <string.h>

class StringProcessor
{
	char * str;
public:
	StringProcessor(char * str) : str(str) {}

	uint8_t isSetParam(char * param) {
		return (strstr(str, param) != nullptr);
	}

	uint16_t getUIntValue(char * name) {
		char * type = strstr(str, name);
		char * begin = strchr(type, ':') + 1;
		return strtol(begin, &type, 10);
	}

}; //StringProcessor

#endif //__STRINGPROCESSOR_H__
