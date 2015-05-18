#ifndef DBRECORD_H
#define DBRECORD_H

#include <vector>

#include "dbfield.h"
#include "dbkey.h"

class DBRecord
{
public:
	DBRecord(int num);
	DBRecord(const std::vector <DBField> &fields, const std::vector <int> &key_fields);
	bool operator<(const DBRecord &r) const;
	DBField& operator[](int id);

	void setKeyFields(const std::vector <int> &key_fields);

	size_t size() const;
	const DBKey& getKey() const;
	const std::vector <DBField>& getFields() const;
private:
	std::vector <DBField> fields_;
	DBKey key_;
};

#endif
