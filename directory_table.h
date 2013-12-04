/*
 * directory_table.h
 *
 *  Created on: Nov 30, 2013
 *      Author: visitor15
 */

#ifndef DIRECTORY_TABLE_H_
#define DIRECTORY_TABLE_H_

#include <vector>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include "global_vars.h"

/*
 *	STRUCT		directory_entry_t		- 32 byte data structure representing
 *										  a file or folder entry into the directory table.
 */
struct directory_entry_t {
	char name[8];
	char extension[3];
	uint8_t attrs;
	unsigned short reserved;
	unsigned short creation_time;
	unsigned short creation_date;
	unsigned short last_access_date;
	unsigned short reserved_2;
	unsigned short last_modified_time;
	unsigned short last_modified_date;
	uint16_t starting_cluster;
	unsigned long size;

	directory_entry_t() {
		memset(name, ' ', 8);
		memset(extension, ' ', 3);
		reserved = 0;
		creation_time = 0;
		creation_date = 0;
		last_access_date = 0;
		reserved_2 = 0;
		last_modified_time = 0;
		last_modified_date = 0;
		starting_cluster = -1;
		size = 0;
		attrs = 0;
	}
};

/*
 *	CLASS		directory_table			- Managing class for the volume's directory table.
 */
class directory_table {
private:
	// Array of 'directory_entry_t' structs representing the directory table of the volume.
//	directory_entry_t DIRECTORY[(ROOT_DIR_SIZE_IN_SECTORS * SECTOR_SIZE_IN_BYTES) / DIR_ENTRY_SIZE_IN_BYTES];

	std::vector<directory_entry_t> DIRECTORY;
public:
	directory_table();
	virtual ~directory_table();

	bool create_entry(const directory_entry_t dir_entry);
	bool delete_entry_at(const unsigned int index);
	bool rename_entry_at(const char old_name[], const char new_name[]);



	directory_entry_t* get_entry_at(const unsigned int index);
	directory_entry_t* get_entry_by_name(const std::string file_name);

	void list_contents();
};

#endif /* DIRECTORY_TABLE_H_ */
