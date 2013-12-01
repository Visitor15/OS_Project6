/*
 * global_vars.h
 *
 *  Created on: Nov 30, 2013
 *      Author: visitor15
 */

#ifndef GLOBAL_VARS_H_
#define GLOBAL_VARS_H_

#include <string>
#include <time.h>

static std::string DRIVE_FILENAME = "fdd.flp";
static std::string EMPTY_DRIVE_FILENAME = "blankfdd.flp";
static std::string BOOT_RECORD_FILENAME = "boot.bin";

static std::string TEST_FILENAME = "WHALE.TXT";
static std::string TEST_FILENAME_2 = "EMILY.TXT";

static int DATA_SEG_OFFSET = 33;

static const unsigned int SECTOR_SIZE_IN_BYTES = 512;
static const unsigned int ROOT_DIR_SIZE_IN_SECTORS = 14;
static const unsigned int DIR_ENTRY_SIZE_IN_BYTES = 32;

enum FILE_ATTRS {
	READ_ONLY		= 0x01,
	HIDDEN			= 0x02,
	SYSTEM			= 0x04,
	VOLUME_LABEL	= 0x08,
	SUB_DIRECTORY	= 0x10,
	ARCHIVE			= 0x20,
};

static time_t get_current_time() {
	return time(0);
}

#endif /* GLOBAL_VARS_H_ */
