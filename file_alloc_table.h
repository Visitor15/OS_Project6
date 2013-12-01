/*
 * file_alloc_table.h
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#ifndef FILE_ALLOC_TABLE_H_
#define FILE_ALLOC_TABLE_H_

#include <vector>
#include <string.h>

#include "global_vars.h"
#include "directory_table.h"

enum FAT_ENTRY_VALUE {
	FREE_SECTOR = 0x00,
	RESERVED = 0xFF0,
	BAD_SECTOR = 0xFF7,
	END_OF_FILE = 0xFF8
};

struct drive_sector_t {
	char sector_data[SECTOR_SIZE_IN_BYTES];

	drive_sector_t() {
		// Do nothing
	}

	drive_sector_t(char data[]) {
		memcpy(sector_data, data, SECTOR_SIZE_IN_BYTES);
	}

	void copy_data(char data[]) {
		memcpy(sector_data, data, SECTOR_SIZE_IN_BYTES);
	}
};

// 12 bit file allocation table entry.
struct __attribute__((packed)) fat_entry_t {
	unsigned int entry :12;

	fat_entry_t() :
			entry(FREE_SECTOR) {
	}
	;
};

class file_alloc_table {
private:
	std::vector<fat_entry_t> FILE_ALLOCATION_TABLE;

	unsigned long sector_count;

	void init(const int num_drive_sectors);
public:
	/*
	 *	CONSTRUCTORS
	 */
	file_alloc_table();
	file_alloc_table(const int num_drive_sectors);

	/*
	 * 	DESTRUCTOR
	 */
	virtual ~file_alloc_table();

	/*
	 *	FUNCTION
	 */
	void add_sector_entry();

	/*
	 * 	FUNCTION
	 */
	std::vector<fat_entry_t> get_allocation_table();

	/*
	 *	FUNCTION
	 */
	fat_entry_t* request_specified_free_sectors(int count);

	/*
	 *	FUNCTION
	 */
	fat_entry_t* get_sector_at(long index);

	/*
	 *	FUNCTION
	 */
	void get_sectors_for_file(uint16_t starting_cluster, int num_sectors, std::vector<fat_entry_t> &entry_list);

};

#endif /* FILE_ALLOC_TABLE_H_ */
