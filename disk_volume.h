/*
 * disk_volume.h
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#ifndef DISK_VOLUME_H_
#define DISK_VOLUME_H_

#include <stdlib.h>

struct boot_ctrl_blk {

};

struct file_t {

};

struct directory_entry {

};

struct volume_t {

};

class disk_volume {
private:
	disk_volume();
	disk_volume(disk_volume const&);

	static disk_volume* m_pInstance;

public:
	static disk_volume* get_instance();
};



#endif /* DISK_VOLUME_H_ */
