/*
 * disk_volume.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#include "disk_volume.h"

disk_volume::disk_volume () {
	init_volume();
}

disk_volume::disk_volume (disk_volume const&) {
	init_volume();
}

disk_volume* disk_volume::get_instance () {
	if(m_pInstance == NULL) {
		static disk_volume _self;
		m_pInstance = &_self;
	}

	return m_pInstance;
}

void disk_volume::init_volume() {
	read_drive();
}

void disk_volume::read_drive() {
	std::ifstream i_stream (DRIVE_FILENAME.c_str(), std::ios::in | std::ios::binary);

	i_stream.seekg(0, std::ios::end);
	DRIVE_LENGTH = i_stream.tellg();

	if(i_stream.is_open()) {
		curr_index = 0;
		while(i_stream.good()) {
			// Reading file a sector length at a time.
			i_stream.getline(buffer, SECTOR_SIZE_IN_BYTES);
			// Adding data to DRIVE_ARRAY.
			add_sector_data_from_buf(buffer);
			// Adding FAT entry.
			F_ALLOC_TABLE.add_sector_entry();
		}
	}
}

void disk_volume::add_sector_data_from_buf(char buf[]) {
	DRIVE_ARRAY.push_back(drive_sector_t(buf));
	++curr_index;
}


