#ifndef DBFIELD_H
#define DBFIELD_H

#include <iostream>

struct DBField
{
	DBField() {type = NIL;}
	bool operator==(const DBField &f) const;
	bool operator!=(const DBField &f) const;
	union {
		int integer;
	} value;
	enum Type {NIL, INTEGER} type;
};

std::istream& operator>>(std::istream &in, DBField &field);
std::ostream& operator<<(std::ostream &out, const DBField &field);

#endif
