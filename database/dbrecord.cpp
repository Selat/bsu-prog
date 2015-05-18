#include "dbrecord.h"

DBRecord::DBRecord(int num) :
	fields_(num)
{
}

DBRecord::DBRecord(const std::vector <DBField> &fields, const std::vector<int> &key_fields) :
	fields_(fields),
	key_(fields, key_fields)
{
}

bool DBRecord::operator<(const DBRecord &r) const
{
	return key_ < r.key_;
}

DBField& DBRecord::operator[](int id)
{
	return fields_[id];
}

void DBRecord::setKeyFields(const std::vector <int> &key_fields)
{
	key_ = DBKey(fields_, key_fields);
}

size_t DBRecord::size() const
{
	return fields_.size();
}

const DBKey& DBRecord::getKey() const
{
	return key_;
}

const std::vector<DBField>& DBRecord::getFields() const
{
	return fields_;
}
