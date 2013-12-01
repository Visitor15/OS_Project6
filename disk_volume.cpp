/*
 * disk_volume.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#include "disk_volume.h"

disk_volume::disk_volume() {
	init_volume();
}

disk_volume::disk_volume(disk_volume const&) {
	init_volume();
}

disk_volume* disk_volume::get_instance() {
	if (m_pInstance == NULL) {
		static disk_volume _self;
		m_pInstance = &_self;
	}

	return m_pInstance;
}

void disk_volume::init_volume() {
	read_drive();
}

void disk_volume::read_drive() {
	std::ifstream i_stream(DRIVE_FILENAME.c_str(),
			std::ios::in | std::ios::binary);

	/*
	 * If 'DRIVE_FILENAME' does not exist, we create it and write the boot loader
	 * to sector 0 in the process. The remaining sectors are copied from 'EMPTY_DRIVE_FILENAME'.
	 */
	if (!i_stream.is_open()) {
		i_stream.close();
		std::ofstream o_stream(DRIVE_FILENAME.c_str());
		write_boot_record(o_stream);
		i_stream.open(DRIVE_FILENAME.c_str(), std::ios::in | std::ios::binary);
	}

	i_stream.seekg(0, i_stream.end);
	DRIVE_LENGTH = i_stream.tellg();
	i_stream.seekg(0, i_stream.beg);
	if (i_stream.is_open()) {
		curr_index = 0;
		while (i_stream.good()) {
			memset(buffer, 0, SECTOR_SIZE_IN_BYTES);
			// Reading file a sector length at a time.
			i_stream.read(buffer, SECTOR_SIZE_IN_BYTES);
			// Ensuring we read something.
			if (i_stream.gcount() > 0) {
				// Adding data to DRIVE_ARRAY.
				add_sector_data_from_buf(buffer);
				// Adding FAT entry.
				F_ALLOC_TABLE.add_sector_entry();
			}
		}

		i_stream.close();
	}

	write_primary_fat(F_ALLOC_TABLE.get_allocation_table());
}

void disk_volume::add_sector_data_from_buf(char buf[]) {
	DRIVE_ARRAY.push_back(drive_sector_t(buf));
	++curr_index;
}

void disk_volume::write_boot_record(std::ofstream &out_stream) {
	std::ifstream i_stream(BOOT_RECORD_FILENAME.c_str(),
			std::ios::in | std::ios::binary);

	i_stream.seekg(0, i_stream.end);
	int length = i_stream.tellg();
	i_stream.seekg(0, i_stream.beg);

	// We're reading exactly 512 bytes here.
	if (i_stream.is_open()) {
		memset(buffer, 0, SECTOR_SIZE_IN_BYTES);
		// Reading file a sector length at a time.
		i_stream.read(buffer, SECTOR_SIZE_IN_BYTES);
		// Writing contents of boot record to floppy image.
		out_stream.write(buffer, SECTOR_SIZE_IN_BYTES);

		i_stream.close();
		i_stream.open(EMPTY_DRIVE_FILENAME.c_str(),
				std::ios::in | std::ios::binary);

		i_stream.seekg(0, i_stream.end);
		length = i_stream.tellg();
		i_stream.seekg(0, i_stream.beg);
		// Skipping the first 512 bytes since we've already written to that sector.
		i_stream.seekg(SECTOR_SIZE_IN_BYTES);

		while (i_stream.good()) {
			memset(buffer, 0, SECTOR_SIZE_IN_BYTES);
			// Reading file a sector length at a time.
			i_stream.read(buffer, SECTOR_SIZE_IN_BYTES);
			// Ensuring we have something to write.
			if (i_stream.gcount() > 0) {
				out_stream.write(buffer, SECTOR_SIZE_IN_BYTES);
			}
		}

		out_stream.close();
		i_stream.close();
	}
}


// COMPLETE ME!
void disk_volume::write_primary_fat(std::vector<fat_entry_t> alloc_table) {
	std::ofstream o_stream(DRIVE_FILENAME.c_str(), std::ios::binary);
	o_stream.seekp(0, o_stream.beg);
	o_stream.seekp(SECTOR_SIZE_IN_BYTES);

	struct double_entry_container {
		unsigned int : 24;
	};

	// 3 byte (24-bit) char[] to neatly pack 2 12-bit FAT entries.
	char buf[3];
	double length = 0;
	for(int i = 1; i < alloc_table.size(); i++) {
		memset(buf, 0, sizeof(buf) );

		fat_entry_t entries[2];
		entries[0] = alloc_table.at(i - 1);
		entries[1] = alloc_table.at(i);
		double_entry_container* container;
		length = (double) sizeof(entries);

		o_stream.write((char*) container, 3);
	}
}

