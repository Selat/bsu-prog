#include "dbfilein.h"

#include <sstream>

DBFileIn::DBFileIn(DBFileIn&& file) :
	filename_(file.filename_),
	field_names_(file.field_names_),
	entry_(file.entry_),
	key_fields_(file.key_fields_)
{
}

DBFileIn::DBFileIn(const std::string &filename, int fields_num) :
	filename_(filename), field_names_(fields_num), entry_(fields_num)
{
	for(int i = 0; i < fields_num; ++i) {
		std::stringstream ss;
		ss << (i + 1);
		field_names_[i] = ss.str();
	}
}

bool DBFileIn::open()
{
	file_.open(filename_.c_str());
	if(!file_.good()) {
		return false;
	} else {
		for(size_t i = 0; i < field_names_.size(); ++i) {
			file_ >> field_names_[i];
		}
		return true;
	}
}

bool DBFileIn::eof() const
{
	return file_.eof();
}

void DBFileIn::close()
{
	file_.close();
}

bool DBFileIn::readNextEntry()
{
	if(!file_.good()) {
		return false;
	} else {
		for(size_t i = 0; i < entry_.size(); ++i) {
			if(!(file_ >> entry_[i])) return false;
		}
		entry_.setKeyFields(key_fields_);
		return true;
	}
}

const DBRecord& DBFileIn::getCurrentEntry() const
{
	return entry_;
}

DBKey DBFileIn::getCurrentKey() const
{
	return DBKey(entry_.getFields(), key_fields_);
}

void DBFileIn::setFieldNames(const std::initializer_list<std::string> &names)
{
	field_names_.assign(names.begin(), names.end());
}

void DBFileIn::setKeyFields(const std::initializer_list<int> &l)
{
	key_fields_.assign(l.begin(), l.end());
	entry_.setKeyFields(key_fields_);
}

const std::vector <std::string>& DBFileIn::getFieldNames() const
{
	return field_names_;
}
