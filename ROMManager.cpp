/*
 * ROMManager.cpp
 *
 *  Created on: 07/gen/2015
 *      Author: stefano
 */


#include "DATFile.h"

#include <cstdlib>
#include <iostream>

#include "database/Database.h"
#include "database/DatabaseFactory.h"
#include "database/Schema.h"

int main(int argc, char** argv)
{
	if (argc < 2)
		exit(-1);

	DatabaseFactory dbFactory;
	Database* db = dbFactory.GetDatabase("SQLite");
	int status = db->Open("test.db");
	if (status == 0)
		status = Schema::Init(*db);
	if (status != 0)
		std::cerr << "Error: " << status << std::endl;

	DATFile file(argv[1]);
	file.ParseInto(*db);

	db->Close();
	delete db;

	return 0;
}


