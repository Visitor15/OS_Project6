//============================================================================
// Name        : OS_Project6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>

#include "disk_volume.h"

int main(void) {
	puts("Hello World!!!");

	disk_volume::get_instance();

	return EXIT_SUCCESS;
}
