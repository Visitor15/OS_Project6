/*
 * file_alloc_table.h
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#ifndef FILE_ALLOC_TABLE_H_
#define FILE_ALLOC_TABLE_H_

enum FAT_ENTRY_VALUE {
	FREE_SECTOR	= 0x000,
	NOT_ALLOWED = 0x0001 | 0x0002,
	BAD_SECTOR	= 0xFFF7,
	EOF			= 0xFFF8
};

// 12 bit file allocation table entry.
struct fat_entry_t {
	unsigned int entry : 12;

	fat_entry_t() : entry(FREE_SECTOR) {};
} __attribute__((packed));

class file_alloc_table {
private:
	fat_entry_t* FILE_ALLOCATION_TABLE;

	void init(const int num_vol_sectors);
public:
	file_alloc_table (const int num_vol_sectors);
	virtual ~file_alloc_table ();


};

#endif /* FILE_ALLOC_TABLE_H_ */
