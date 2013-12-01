/*
 * file_alloc_table.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#include "file_alloc_table.h"

file_alloc_table::file_alloc_table() {
	init(0);
}

file_alloc_table::file_alloc_table(const int num_drive_sectors) {
	init(num_drive_sectors);
}

file_alloc_table::~file_alloc_table() {

}

void file_alloc_table::init(const int num_drive_sectors) {
	sector_count = num_drive_sectors;
	for (unsigned int i = 0; i < sector_count; i++) {
		FILE_ALLOCATION_TABLE.push_back(fat_entry_t());
	}
}

void file_alloc_table::add_sector_entry() {
	FILE_ALLOCATION_TABLE.push_back(fat_entry_t());
	++sector_count;
}

std::vector<fat_entry_t> file_alloc_table::get_allocation_table() {
	return FILE_ALLOCATION_TABLE;
}

fat_entry_t* file_alloc_table::request_specified_free_sectors(int count) {
	fat_entry_t* free_sectors[count];
	long curr_count = 0;
	long head_index = 0;
	long length = FILE_ALLOCATION_TABLE.size();
	for (int i = DATA_SEG_OFFSET; i < FILE_ALLOCATION_TABLE.size(); i++) {
		if (FILE_ALLOCATION_TABLE.at(i).entry == FREE_SECTOR) {
			free_sectors[curr_count] = &FILE_ALLOCATION_TABLE[i];
			if (curr_count > 0) {
				(*free_sectors[curr_count - 1]).entry = i;
			} else {
				// Head index
				head_index = i;
			}
			curr_count++;

			// Attempting to break loop early if possible.
			if (curr_count == count) {
				break;
			}
		}
	}

	// If we were able to allocate enough sectors, we return those.
	if (curr_count == count) {
		(*free_sectors[count - 1]).entry = head_index;
		return *free_sectors;
	}

	// Otherwise, drive is full. Not enough sectors available.
	return 0;
}

fat_entry_t* file_alloc_table::get_sector_at(long index) {
	return &FILE_ALLOCATION_TABLE[index];
}

void file_alloc_table::get_sectors_for_file(uint16_t starting_cluster,
		int num_sectors, fat_entry_t* entry_list) {
	entry_list[0] = FILE_ALLOCATION_TABLE[starting_cluster];
	for (int i = 1; i < num_sectors; i++) {
		entry_list[i] = FILE_ALLOCATION_TABLE[entry_list[i - 1].entry];
	}
}

