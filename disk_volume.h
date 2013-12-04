/*
 * disk_volume.h
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#ifndef DISK_VOLUME_H_
#define DISK_VOLUME_H_

#include <vector>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <math.h>

#include "global_vars.h"
#include "file_alloc_table.h"
#include "directory_table.h"

struct boot_ctrl_blk {
	// 512 bytes
};



struct volume_t {

};

/*
 *	CLASS		disk_volume
 */
class disk_volume {
private:
	/*
	 * 	VARIABLES
	 */
	std::vector<drive_sector_t> DRIVE_ARRAY;
	file_alloc_table F_ALLOC_TABLE;
	directory_table DIR_TABLE;

	unsigned long curr_index;

	char buffer[SECTOR_SIZE_IN_BYTES];

	/*
	 *	CONSTRUCTORS
	 */
	disk_volume ();
	disk_volume (disk_volume const&);

	/*
	 *	FUNCTION		init_volume
	 */
	void init_volume ();
	void read_drive ();
	void add_sector_data_from_buf(char buf[], long length);
	void write_boot_record(std::ofstream &out_stream);
	void write_primary_fat(std::vector<fat_entry_t> alloc_table);
	void create_dir_entry(std::string file_name, directory_entry_t& dir_entry, long head_sector);

	drive_sector_t* get_data_sector_at(long index);

public:
	unsigned long DRIVE_LENGTH;

	static disk_volume* get_instance ();

	void copy_file_to_drive(std::string file_name, directory_entry_t dir_entry);
	std::vector<drive_sector_t> get_file_by_name (std::string file_name);
	void print_file(std::string file_name);
	void print_drive_contents();
};

static disk_volume* m_pInstance;

#endif /* DISK_VOLUME_H_ */
