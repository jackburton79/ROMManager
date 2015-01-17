/*
 * Schema.h
 *
 *  Created on: 16/gen/2015
 *      Author: stefano
 */

#ifndef SCHEMA_H_
#define SCHEMA_H_

#include <map>
#include <string>

extern const char* kRomsTable;
extern const char* kGamesTable;

class Schema {
public:
	static int Init(Database& database);
	static int InsertRomRow(Database& database,
				std::map<std::string, std::string>& values);
};

#endif /* SCHEMA_H_ */
