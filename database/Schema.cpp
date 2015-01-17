/*
 * Schema.cpp
 *
 *  Created on: 16/gen/2015
 *      Author: stefano
 */

#include "Database.h"
#include "Schema.h"


#include <cstdlib>
#include <iostream>
#include <sstream>

const char* kRomsTable = "roms";
const char* kGamesTable = "games";
const char* kCreateGamesTable =
							"CREATE TABLE main.games"\
							"(id INT PRIMARY KEY NOT NULL, "\
							"name STRING)";

const char* kCreateRomsTable =
							"CREATE TABLE main.roms"\
							"(id INT PRIMARY KEY NOT NULL, "\
							"game_id int, name STRING, size UNSIGNED INT, "\
							"crc UNSIGNED INT, sha1 UNSIGNED BIG INT)";

/* static */
int
Schema::Init(Database& database)
{
	int status = database.ExecuteSQL(kCreateGamesTable);
	if (status == 0)
		status = database.ExecuteSQL(kCreateRomsTable);
	return status;
}


/* static */
int
Schema::InsertRomRow(Database& database,
		std::map<std::string, std::string>& values)
{
	unsigned long crc = ::strtoul(values["crc"].c_str(), NULL, 16);
	unsigned long long sha1 = ::strtoull(values["sha1"].c_str(), NULL, 16);

	std::ostringstream formatter;
	std::string sql = "INSERT INTO ";
	sql.append(kRomsTable);
	sql.append(" (id, game_id, name, size, crc, sha1) ");
	sql.append("VALUES (");
	sql.append("0, ");
	sql.append("0, ");
	sql.append("\"");
	sql.append(values["name"]);
	sql.append("\"");
	sql.append(", ");
	sql.append(values["size"]);
	sql.append(", ");
	formatter << crc;
	sql.append(formatter.str());
	sql.append(", ");
	formatter.str("");
	formatter << sha1;
	sql.append(formatter.str());
	sql.append(")");
	std::cout << "InsertRomRow: " << sql << std::endl;

	return database.ExecuteSQL(sql.c_str());
}
