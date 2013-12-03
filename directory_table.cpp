/*
 * directory_table.cpp
 *
 *  Created on: Nov 30, 2013
 *      Author: visitor15
 */

#include <iostream>

#include "directory_table.h"

directory_table::directory_table() {
	// TODO Auto-generated constructor stub

}

directory_table::~directory_table() {
	// TODO Auto-generated destructor stub
}

directory_entry_t* directory_table::get_entry_by_name(
		const std::string file_name) {
	for (int i = 0; i < DIRECTORY.size(); i++) {
		std::string entry_name(DIRECTORY.at(i).name);
		entry_name.append(".").append(DIRECTORY.at(i).extension);
		if (entry_name.find(file_name) != std::string::npos) {



			return &DIRECTORY[i];
		}
	}

	return 0;
}

bool directory_table::create_entry(directory_entry_t dir_entry) {

	DIRECTORY.push_back(dir_entry);

	std::cout << "Added directory entry with head index: "
			<< DIRECTORY.at(DIRECTORY.size() - 1).starting_cluster << std::endl;

	return false;
}
