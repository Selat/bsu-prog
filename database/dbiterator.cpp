#include "dbiterator.h"

#include "dbexceptions.h"

DBIterator::DBIterator(const std::initializer_list<DBFileIn*> &files) :
	files_(files)
{
}

DBIterator::DBIterator(const std::vector<DBFileIn*> &files) :
	files_(files)
{
}

void DBIterator::init()
{
	for(auto f : files_) {
		f->open();
		have_entry_.assign(files_.size(), false);
		entry_.resize(files_.size());
		used_.assign(files_.size(), false);
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
	int min_key_id = 0;
	for(size_t i = 0; i < files_.size(); ++i) {
		if(have_entry_[i] && (!found_min || (entry_[i].getKey() < min_key)
		                      || ((entry_[i].getKey() == min_key)
		                          && (entry_[i].getKey().getFields().size() > min_key.getFields().size())))) {
			min_key = entry_[i].getKey();
			min_key_id = i;
			found_min = true;
		}
	}
	if(!found_min) {
		return false;
	}

	// Looks like we are going to reuse old record, so we have to move iterators forward in all files
	while(used_[min_key_id]) {
		have_entry_[min_key_id] = files_[min_key_id]->readNextEntry();
		entry_[min_key_id] = files_[min_key_id]->getCurrentEntry();
		used_[min_key_id] = false;
		found_min = false;
		for(size_t i = 0; i < files_.size(); ++i) {
			if(have_entry_[i] && (!found_min || (entry_[i].getKey() < min_key)
			                      || ((entry_[i].getKey() == min_key)
			                          && (entry_[i].getKey().getFields().size() > min_key.getFields().size())))) {
				min_key = entry_[i].getKey();
				min_key_id = i;
				found_min = true;
			}
		}
		if(!found_min) {
			return false;
		}
	}

	for(size_t i = 0; i < files_.size(); ++i) {
		if(!(entry_[i].getKey() == min_key)) {
			throw DBException("Unmatched keys");
		}
	}

	// Calculate required size of the key
	size_t key_size = 0;
	for(size_t i = 0; i < files_.size(); ++i) {
		if(have_entry_[i] && (entry_[i].getKey() == min_key) && (entry_[i].getKey().getFields().size() > key_size)) {
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
	cur_entry_.clear();
	cur_entry_.resize(key_size + fields_size);

	// Fill key of the record
	for(size_t i = 0; i < key_size; ++i) {
		cur_entry_.getFields()[i] = min_key.getFields()[i];
	}
	// Combine all available fields from the files
	int cur_field_id = key_size;
	for(size_t i = 0; i < files_.size(); ++i) {
		if(have_entry_[i] && (entry_[i].getKey() == min_key)) {
			for(size_t j = entry_[i].getKey().getFields().size(); j < entry_[i].getFields().size(); ++j) {
				cur_entry_.getFields()[cur_field_id++] = entry_[i].getFields()[j];
			}
		}
	}

	// Move iterator in each file forward
	for(size_t i = 0; i < files_.size(); ++i) {
		if(have_entry_[i] && (entry_[i].getKey() == min_key)) {
			if(entry_[i].getKey().getFields().size() == min_key.getFields().size()) {
				have_entry_[i] = files_[i]->readNextEntry();
				entry_[i] = files_[i]->getCurrentEntry();
			} else {
				used_[i] = true;
			}
		}
	}
	return true;
}

const DBRecord& DBIterator::getCurrentEntry() const
{
	return cur_entry_;
}
