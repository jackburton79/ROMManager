/*
 * DATFile.h
 *
 *  Created on: 07/gen/2015
 *      Author: stefano
 */

#ifndef DATFILE_H_
#define DATFILE_H_

class DATFile {
public:
	DATFile(const char* file);
	~DATFile();

	int Parse();
};

#endif /* DATFILE_H_ */
