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
	for(size_t i = 0; i < files_.size(); ++i) {
		if(!have_entry_[i] && !files_[i]->eof()) {
			if(files_[i]->readNextEntry()) {
				entry_[i] = files_[i]->getCurrentEntry();
				have_entry_[i] = true;
			} else {
				have_entry_[i] = false;
			}
		}
	}

	// Firstly we find the minimum key of all available
	bool found_min = false;
	DBKey min_key;
	for(size_t i = 0; i < files_.size(); ++i) {
		if(have_entry_[i] && (!found_min || (entry_[i].getKey() < min_key))) {
			min_key = entry_[i].getKey();
			found_min = true;
		}
	}
	if(!found_min) {
		return false;
	}

	// Calculate required size of the key
	size_t key_size = 0;
	for(size_t i = 0; i < files_.size(); ++i) {
		if(have_entry_[i] && (entry_[i].getKey().getFields().size() > key_size)) {
			key_size = entry_[i].getKey().getFields().size();
		}
	}
	// Calculate number of information fields (fields that are not key fields)
	int fields_size = 0;
	for(size_t i = 0; i < files_.size(); ++i) {
		if(have_entry_[i] && (entry_[i].getKey() == min_key)) {
			int curnum = entry_[i].getFields().size();
			curnum -= entry_[i].getKey().getFields().size();
			fields_size += curnum;
		}
	}
}

const std::vector <DBField>& DBIterator::getCurrentEntry()
{
}
