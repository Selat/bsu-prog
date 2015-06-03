#include "dbrecord.h"

DBRecord::DBRecord()
{
}

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

const DBField& DBRecord::operator[](int id) const
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

void DBRecord::clear()
{
	fields_.clear();
}

void DBRecord::resize(size_t size)
{
	fields_.resize(size);
}

const DBKey& DBRecord::getKey() const
{
	return key_;
}

const std::vector<DBField>& DBRecord::getFields() const
{
	return fields_;
}

std::vector<DBField>& DBRecord::getFields()
{
	return fields_;
}

std::ostream& operator<<(std::ostream &out, const DBRecord &r)
{
	for(size_t i = 0; i + 1 < r.size(); ++i) {
		out << r[i] << " ";
	}
	if(r.size() > 0) {
		out << r[r.size() - 1] << std::endl;
	}
	return out;
}
