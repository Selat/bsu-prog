#include "dbfield.h"

bool DBField::operator==(const DBField &f) const
{
	if(f.type != type) {
		return false;
	} else {
		switch(type) {
		case NIL:
			return true;
		case INTEGER:
			return (value.integer == f.value.integer);
		default:
			return false;
		}
	}
}

bool DBField::operator!=(const DBField &f) const
{
	return !(*this == f);
}

std::istream& operator>>(std::istream &in, DBField &field)
{
	in >> field.value.integer;
	return in;
}

std::ostream& operator<<(std::ostream &out, const DBField &field)
{
	out << field.value.integer;
	return out;
}
