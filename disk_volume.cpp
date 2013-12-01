/*
 * disk_volume.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#include "disk_volume.h"

#include <string>

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

		(*F_ALLOC_TABLE.get_sector_at(0)).entry = RESERVED;
		i_stream.close();
	}

//	write_primary_fat(F_ALLOC_TABLE.get_allocation_table());
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

		fat_entry_t* fat_entry = F_ALLOC_TABLE.get_sector_at(0);

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
		unsigned int :24;
	};

	// 3 byte (24-bit) char[] to neatly pack 2 12-bit FAT entries.
	char buf[3];
	double length = 0;
	for (int i = 1; i < alloc_table.size(); i++) {
		memset(buf, 0, sizeof(buf));

		fat_entry_t entries[2];
		entries[0] = alloc_table.at(i - 1);
		entries[1] = alloc_table.at(i);
		double_entry_container* container;
		length = (double) sizeof(entries);

		o_stream.write((char*) container, 3);

	}

	o_stream.close();
}

void disk_volume::copy_file_to_drive(std::string file_name) {
	std::ifstream i_stream(file_name.c_str(), std::ios::in | std::ios::binary);
	long head_sector = -1;
	if (i_stream.is_open()) {
		memset(buffer, 0, SECTOR_SIZE_IN_BYTES);

		i_stream.seekg(0, i_stream.end);
		long file_length = i_stream.tellg();
		i_stream.seekg(0, i_stream.beg);

		// Rounding up the number of sectors required for writing file
		int sectors_required = ceil(
				(double) file_length / (double) SECTOR_SIZE_IN_BYTES);

		fat_entry_t* sectors = F_ALLOC_TABLE.request_specified_free_sectors(
				sectors_required);

		if (sectors > 0) {
			// We saved the head of the file sector to the last free sector entry.
			long curr_index = sectors[sectors_required - 1].entry;
			head_sector = curr_index;
			sectors[sectors_required - 1].entry = END_OF_FILE;

			for (int i = 0; i < sectors_required; i++) {
				if (i_stream.good()) {
					memset(buffer, 0, SECTOR_SIZE_IN_BYTES);
					// Reading file a sector length at a time.
					i_stream.read(buffer, SECTOR_SIZE_IN_BYTES);

					// Ensuring we have something to write.
					if (i_stream.gcount() > 0) {
						get_data_sector_at(curr_index)->copy_data(buffer);
					}
					curr_index = sectors[i].entry;
				}
			}
		}
		if (i_stream.is_open()) {
			i_stream.close();
		}
		// We make the directory entry last.
		DIR_TABLE.create_entry(create_dir_entry(file_name, head_sector));
	}
}

directory_entry_t disk_volume::create_dir_entry(std::string file_name,
		long head_sector) {
	directory_entry_t dir_entry;
	time_t curr_time = get_current_time();
	std::ifstream i_stream(file_name.c_str(), std::ios::in | std::ios::binary);
	i_stream.seekg(0, i_stream.beg);
	i_stream.seekg(0, i_stream.end);
	dir_entry.size = i_stream.tellg();
	i_stream.seekg(0, i_stream.beg);

	int pos = file_name.find(".");
	std::string title = file_name.substr(0, pos);
	std::string extension = file_name.substr(pos + 1);

	dir_entry.starting_cluster = head_sector;

	memcpy(dir_entry.name, title.c_str(), 8);
	memcpy(dir_entry.extension, extension.c_str(), 43);

	return dir_entry;
}

std::vector<drive_sector_t> disk_volume::get_file_by_name(
		std::string file_name) {
	std::vector<drive_sector_t> file_sectors;
	directory_entry_t* dir_entry = DIR_TABLE.get_entry_by_name(file_name);
	if (dir_entry > 0) {
		unsigned long num_sectors = ceil(
				dir_entry->size / (double) SECTOR_SIZE_IN_BYTES);
		fat_entry_t fat_entry_list[num_sectors];
		F_ALLOC_TABLE.get_sectors_for_file(dir_entry->starting_cluster,
				num_sectors, fat_entry_list);

		for (int i = 0; i < num_sectors; i++) {
			file_sectors.push_back(DRIVE_ARRAY[fat_entry_list[i].entry]);
		}
	}

	return file_sectors;
}

void disk_volume::print_drive_contents() {
	std::cout << "==========================================" << std::endl;
	std::cout << "| PRINTING DRIVE CONTENT" << std::endl;
	std::cout << "==========================================" << std::endl;

	std::ofstream o_stream("test_1.txt", std::ios::binary);
	long length = DRIVE_ARRAY.size();
	for (int i = 0; i < DRIVE_ARRAY.size(); i++) {
		std::string data = DRIVE_ARRAY.at(i).sector_data;
//		std::cout << data << std::endl;
//		std::cout << "=============================" << std::endl;

		o_stream.write(DRIVE_ARRAY.at(i).sector_data, SECTOR_SIZE_IN_BYTES);
	}

	o_stream.flush();
	o_stream.close();
}

drive_sector_t* disk_volume::get_data_sector_at(long index) {
	return &DRIVE_ARRAY[index];
}

