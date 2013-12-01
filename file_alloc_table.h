/*
 * file_alloc_table.h
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#ifndef FILE_ALLOC_TABLE_H_
#define FILE_ALLOC_TABLE_H_

#include <vector>

enum FAT_ENTRY_VALUE {
	FREE_SECTOR	= 0x000,
	BAD_SECTOR	= 0xFFF7,
};

// 12 bit file allocation table entry.
struct fat_entry_t {
	unsigned int entry : 12;

	fat_entry_t() : entry(FREE_SECTOR) {};
} __attribute__((packed));

class file_alloc_table {
private:
	std::vector<fat_entry_t> FILE_ALLOCATION_TABLE;

	unsigned long sector_count;

	void init(const int num_drive_sectors);
public:
	/*
	 *	CONSTRUCTORS
	 */
	file_alloc_table ();
	file_alloc_table (const int num_drive_sectors);

	/*
	 * 	DESTRUCTOR
	 */
	virtual ~file_alloc_table ();

	/*
	 *	FUNCTION
	 */
	void add_sector_entry();
};

#endif /* FILE_ALLOC_TABLE_H_ */
