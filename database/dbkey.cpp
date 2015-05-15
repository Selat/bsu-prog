#include "dbkey.h"

#include <algorithm>

DBKey::DBKey(const std::vector <DBField> &fields, const std::vector <int> &ids) :
	fields_(ids.size())
{
	for(size_t i = 0; i < ids.size(); ++i) {
		fields_[i] = fields[ids[i]];
	}
}

bool DBKey::operator==(const DBKey &k) const
{
	size_t n = std::min(k.fields_.size(), fields_.size());
	for(size_t i = 0; i < n; ++i) {
		if(fields_[i] != k.fields_[i]) {
			return false;
		}
	}
	return true;
}

bool DBKey::operator<(const DBKey &k) const
{
}
