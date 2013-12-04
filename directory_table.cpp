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
		std::cout << "Looking for entry: " << entry_name << " AND "
				<< DIRECTORY.at(i).extension << std::endl;
		if (entry_name.find(file_name.substr(0, file_name.find(".") - 1)) != std::string::npos
				&& file_name.find(DIRECTORY.at(i).extension)
						!= std::string::npos) {

			std::cout << "FOUND!" << std::endl;

			return &DIRECTORY[i];
		}
	}

	return 0;
}

bool directory_table::create_entry(directory_entry_t dir_entry) {

	DIRECTORY.push_back(dir_entry);

	std::cout << "Added directory entry: " << dir_entry.name
			<< " with head index: "
			<< DIRECTORY.at(DIRECTORY.size() - 1).starting_cluster << std::endl;

	return false;
}
