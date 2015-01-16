/*
 * DatabaseFactory.cpp
 *
 *  Created on: 16/gen/2015
 *      Author: stefano
 */

#include "DatabaseFactory.h"
#include "SQLiteDatabase.h"

DatabaseFactory::DatabaseFactory()
{
}


DatabaseFactory::~DatabaseFactory()
{
}


Database*
DatabaseFactory::GetDatabase(const char* dbType)
{
	return new SQLiteDatabase();
}
