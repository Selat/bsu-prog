#ifndef DBRECORD_H
#define DBRECORD_H

#include <vector>

#include "dbfield.h"
#include "dbkey.h"

class DBRecord
{
public:
	DBRecord();
	DBRecord(int num);
	DBRecord(const std::vector <DBField> &fields, const std::vector <int> &key_fields);
	bool operator<(const DBRecord &r) const;
	DBField& operator[](int id);
	const DBField& operator[](int id) const;

	void setKeyFields(const std::vector <int> &key_fields);

	void clear();
	void resize(size_t size);

	size_t size() const;
	const DBKey& getKey() const;
	const std::vector <DBField>& getFields() const;
	std::vector <DBField>& getFields();
private:
	std::vector <DBField> fields_;
	DBKey key_;
};

std::ostream& operator<<(std::ostream &out, const DBRecord &r);

#endif
