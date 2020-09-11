#ifndef TERMINAL_INFO_H_
#define TERMINAL_INFO_H_

#include <iostream>
#include <string.h>

const bool enable = true;

static void komun( const std::string & _kom) {
	
	static int numb = 0;
	
	if ( enable == true) {	
		std::cout << numb << ":\t" << _kom << std::endl;
		
		numb++;
	}
}


#endif
