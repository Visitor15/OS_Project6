/*
 * global_vars.h
 *
 *  Created on: Nov 30, 2013
 *      Author: visitor15
 */

#ifndef GLOBAL_VARS_H_
#define GLOBAL_VARS_H_

#include <string>

static std::string DRIVE_FILENAME = "fdd.flp";

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

#endif /* GLOBAL_VARS_H_ */
