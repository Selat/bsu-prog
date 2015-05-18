#ifndef DBKEY_H
#define DBKEY_H

#include <vector>

#include "dbfield.h"

class DBKey
{
public:
	DBKey();
	DBKey(const std::vector <DBField> &fields, const std::vector <int> &ids);
	bool operator==(const DBKey &k) const;
	bool operator<(const DBKey &k) const;
	const std::vector <DBField>& getFields() const;
protected:
	std::vector <DBField> fields_;
};

#endif
