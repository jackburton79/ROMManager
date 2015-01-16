/*
 * Schema.cpp
 *
 *  Created on: 16/gen/2015
 *      Author: stefano
 */

#include "Database.h"
#include "Schema.h"

const char* kCreateGamesTable =
							"CREATE TABLE main.games"\
							"(id INT PRIMARY KEY NOT NULL,"\
							"name STRING)";

const char* kCreateRomsTable =
							"CREATE TABLE main.roms"\
							"(id INT PRIMARY KEY NOT NULL,"\
							"game_id int, name STRING, size INT,"\
							"crc INT, sha1 INT)";

int
InitDatabase(Database* database)
{
	int status = database->ExecuteSQL(kCreateGamesTable);
	if (status == 0)
		status = database->ExecuteSQL(kCreateRomsTable);
	return status;
}
