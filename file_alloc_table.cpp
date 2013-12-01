/*
 * file_alloc_table.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#include "file_alloc_table.h"

file_alloc_table::file_alloc_table (const int num_vol_sectors) {
	init(num_vol_sectors);
}

file_alloc_table::~file_alloc_table () {

}

void file_alloc_table::init (const int num_vol_sectors) {
	for (int i = 0; i < num_vol_sectors; i++) {
		FILE_ALLOCATION_TABLE[i] = fat_entry_t();
	}
}

