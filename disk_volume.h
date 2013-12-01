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

#include "global_vars.h"
#include "file_alloc_table.h"
#include "directory_table.h"

struct boot_ctrl_blk {
	// 512 bytes
};

struct drive_sector_t {
	char sector_data[SECTOR_SIZE_IN_BYTES];

	drive_sector_t() {
		// Do nothing
	}

	drive_sector_t(char data[]) {
		memcpy(sector_data, data, SECTOR_SIZE_IN_BYTES);
	}
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
	void add_sector_data_from_buf(char buf[]);

public:
	unsigned long DRIVE_LENGTH;

	static disk_volume* get_instance ();
};

static disk_volume* m_pInstance;

#endif /* DISK_VOLUME_H_ */
