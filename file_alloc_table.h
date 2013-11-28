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

struct fat_entry_t {

};

class file_alloc_table {
public:
	file_alloc_table ();
	virtual ~file_alloc_table ();
};

#endif /* FILE_ALLOC_TABLE_H_ */
