/*
 * file_alloc_table.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#include "file_alloc_table.h"

file_alloc_table::file_alloc_table () {
	init(0);
}

file_alloc_table::file_alloc_table (const int num_drive_sectors) {
	init(num_drive_sectors);
}

file_alloc_table::~file_alloc_table () {

}

void file_alloc_table::init (const int num_drive_sectors) {
	sector_count = num_drive_sectors;
	for (unsigned int i = 0; i < sector_count; i++) {
		FILE_ALLOCATION_TABLE.push_back(fat_entry_t());
	}
}

void file_alloc_table::add_sector_entry () {
	FILE_ALLOCATION_TABLE.push_back(fat_entry_t());
	++sector_count;
}

std::vector<fat_entry_t> file_alloc_table::get_allocation_table() {
	return FILE_ALLOCATION_TABLE;
}

