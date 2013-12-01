/*
 * disk_volume.h
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#ifndef DISK_VOLUME_H_
#define DISK_VOLUME_H_

#include <stdlib.h>
#include <stdint.h>

#include "global_vars.h"
#include "file_alloc_table.h"
#include "directory_table.h"

struct boot_ctrl_blk {
	// 512 bytes
};

struct volume_t {

};

class disk_volume {
private:
	disk_volume() {};
	disk_volume(disk_volume const&) {};

public:
	static disk_volume* get_instance();
};

static disk_volume* m_pInstance;

#endif /* DISK_VOLUME_H_ */
