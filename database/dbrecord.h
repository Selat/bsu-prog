#ifndef DBRECORD_H
#define DBRECORD_H

#include <vector>

#include "dbfield.h"
#include "dbkey.h"

class DBRecord
{
public:
	DBRecord(const std::vector <DBField> &fields, const std::vector <int> &key_fields);
	bool operator<(const DBRecord &r) const;
private:
	std::vector <DBField> fields_;
	DBKey key_;
};

#endif
