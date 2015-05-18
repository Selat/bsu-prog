#ifndef DBITERATOR_H
#define DBITERATOR_H

#include <vector>

#include "dbfile.h"
#include "dbrecord.h"

class DBIterator
{
public:
	DBIterator(const std::initializer_list<DBFile*> &files);
	DBIterator(const std::vector<DBFile*> &files);
	void init();
	bool nextEntry();
	const std::vector <DBField>& getCurrentEntry();
private:
	std::vector <DBFile*> files_;
	std::vector <bool> have_entry_;
	std::vector <DBRecord> entry_;
};

#endif
