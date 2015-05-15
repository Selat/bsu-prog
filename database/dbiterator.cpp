#include "dbiterator.h"

DBIterator::DBIterator(const std::initializer_list<DBFile*> &files) :
	files_(files)
{
}

DBIterator::DBIterator(const std::vector<DBFile*> &files) :
	files_(files)
{
}

void DBIterator::init()
{
	for(auto f : files_) {
		f->open();
		have_entry_.assign(files_.size(), false);
	}
}

bool DBIterator::nextEntry()
{

}

const std::vector <DBField>& DBIterator::getCurrentEntry()
{
}
