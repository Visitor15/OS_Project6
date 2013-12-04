//============================================================================
// Name        : OS_Project6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "disk_volume.h"

int main(void) {
	puts("Hello World!!!");

	disk_volume::get_instance();

	directory_entry_t dir_entry;
	disk_volume::get_instance()->copy_file_to_drive(TEST_FILENAME_3, dir_entry);
	disk_volume::get_instance()->copy_file_to_drive(TEST_FILENAME_2, dir_entry);





//	disk_volume::get_instance()->print_file(TEST_FILENAME);
	disk_volume::get_instance()->print_file(TEST_FILENAME_2);
	disk_volume::get_instance()->print_file(TEST_FILENAME_3);

//	std::vector<drive_sector_t> data_list =
//			disk_volume::get_instance()->get_file_by_name(TEST_FILENAME_2);

//	for (int i = 0; i < data_list.size(); i++) {
//		std::cout << data_list.at(i).sector_data << std::endl;
//	}
//
//	disk_volume::get_instance()->print_drive_contents();

	return EXIT_SUCCESS;
}
