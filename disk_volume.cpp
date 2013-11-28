/*
 * disk_volume.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: visitor15
 */

#include "disk_volume.h"

static disk_volume* disk_volume::get_instance () {

	if(m_pInstance == NULL) {
		static disk_volume _self;
		m_pInstance = &_self;
	}

	return m_pInstance;
}


