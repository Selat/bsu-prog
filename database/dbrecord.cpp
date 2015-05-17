#include "dbrecord.h"

DBRecord::DBRecord(const std::vector <DBField> &fields, const std::vector<int> &key_fields) :
	fields_(fields),
	key_(fields, key_fields)
{
}

bool DBRecord::operator<(const DBRecord &r) const
{
	return key_ < r.key_;
}
