#ifndef DBITERATOR_H
#define DBITERATOR_H

#include <vector>

#include "dbfilein.h"
#include "dbrecord.h"

class DBIterator
{
public:
	DBIterator(const std::initializer_list<DBFileIn*> &files);
	DBIterator(const std::vector<DBFileIn*> &files);
	void init();
	bool nextEntry();
	const DBRecord& getCurrentEntry() const;
private:
	std::vector <DBFileIn*> files_;
	std::vector <bool> have_entry_;
	std::vector <DBRecord> entry_;
	std::vector <bool> used_;
	DBRecord cur_entry_;
};

#endif
