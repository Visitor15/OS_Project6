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

void file_alloc_table::request_specified_free_sectors(
		std::vector<fat_entry_t*> &entry_list, int count) {

	std::cout << "SECTORS REQUIRED: " << count << std::endl;

//	fat_entry_t* free_sectors[count];
	long curr_count = 0;
	long head_index = 0;
	long length = FILE_ALLOCATION_TABLE.size();
	for (int i = DATA_SEG_OFFSET; i < FILE_ALLOCATION_TABLE.size(); i++) {

		if (curr_count == count) {

			// Last item of the vector.
			entry_list.at(entry_list.size() - 1)->entry = head_index;

			std::cout << "ENTRY_LIST SIZE: " << entry_list.size() << std::endl;

			return;
		} else {
			if (FILE_ALLOCATION_TABLE.at(i).entry == FREE_SECTOR) {

				entry_list.push_back(&FILE_ALLOCATION_TABLE[i]);
				if (curr_count == 0) {
					head_index = i;

					std::cout << "Set head to: " << head_index << std::endl;

				}
				//				(*free_sectors[curr_count - 1]).entry = i;
				int temp_val = i;

				entry_list.at(entry_list.size() - 1)->setEntry(i);
				FILE_ALLOCATION_TABLE[entry_list.at(entry_list.size() - 1)->entry].setEntry(i);

				// Attempting to break loop early if possible.
				curr_count++;

			}
		}
	}

//	// If we were able to allocate enough sectors, we return those.
//	if (curr_count == count - 1) {
//		(*free_sectors[curr_count]).entry = head_index;
//		return *free_sectors;
//	}

// Otherwise, drive is full. Not enough sectors available.
}

fat_entry_t* file_alloc_table::get_sector_at(long index) {
	return &FILE_ALLOCATION_TABLE[index];
}

void file_alloc_table::get_sectors_for_file(uint16_t starting_cluster,
		int num_sectors, std::vector<fat_entry_t> &entry_list) {

	entry_list[0] = FILE_ALLOCATION_TABLE[starting_cluster];

	std::cout << "Starting index: " << entry_list.size() << std::endl;

	for (int i = 0; i < num_sectors; i++) {
		std::cout << "HIT HIT HIT HIT HIT " << i << std::endl;
		entry_list.push_back(FILE_ALLOCATION_TABLE[entry_list[i].entry]);
		std::cout << " ADDED ENTRY: " << entry_list.at(i).entry << std::endl;
	}

	long size = entry_list.size();
}

