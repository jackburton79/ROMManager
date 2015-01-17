/*
 * DATFile.h
 *
 *  Created on: 07/gen/2015
 *      Author: stefano
 */

#ifndef DATFILE_H_
#define DATFILE_H_

#include <string>

class Database;
class DATFile {
public:
	DATFile(const char* file);
	~DATFile();

	int ParseInto(Database& database);
private:
	std::string fName;
};

#endif /* DATFILE_H_ */
