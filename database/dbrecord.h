#ifndef DBRECORD_H
#define DBRECORD_H

#include <vector>

#include "dbfield.h"

class DBRecord
{
public:
	DBRecord();
private:
	std::vector <DBField> fields_;
};

#endif
