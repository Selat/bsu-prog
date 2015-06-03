#include "dbfileout.h"

#include <sstream>

DBFileOut::DBFileOut(DBFileOut&& file) :
	filename_(file.filename_),
	field_names_(file.field_names_),
	entry_(file.entry_),
	key_fields_(file.key_fields_)
{
}

DBFileOut::DBFileOut(const std::string &filename, int fields_num) :
	filename_(filename), field_names_(fields_num), entry_(fields_num)
{
	for(int i = 0; i < fields_num; ++i) {
		std::stringstream ss;
		ss << (i + 1);
		field_names_[i] = ss.str();
	}
}

bool DBFileOut::open()
{
	file_.open(filename_.c_str());
	if(!file_.good()) {
		return false;
	} else {
		for(size_t i = 0; i < field_names_.size(); ++i) {
			file_ << field_names_[i] << " ";
		}
		file_ << std::endl;
		return true;
	}
}

void DBFileOut::close()
{
	file_.close();
}

bool DBFileOut::writeEntry()
{
	if(!file_.good()) {
		return false;
	} else {
		for(size_t i = 0; i < entry_.size(); ++i) {
			if(!(file_ << entry_[i] << " ")) return false;
		}
		file_ << std::endl;
		return true;
	}
}

DBRecord& DBFileOut::getCurrentEntry()
{
	return entry_;
}

DBKey DBFileOut::getCurrentKey() const
{
	return DBKey(entry_.getFields(), key_fields_);
}

void DBFileOut::setCurrentKey(const DBKey &k)
{
	for(size_t i = 0; i < key_fields_.size(); ++i) {
		entry_[key_fields_[i]] = k.getFields()[i];
	}
}

void DBFileOut::setFieldNames(const std::initializer_list<std::string> &names)
{
	field_names_.assign(names.begin(), names.end());
}

void DBFileOut::setKeyFields(const std::initializer_list<int> &l)
{
	key_fields_.assign(l.begin(), l.end());
	entry_.setKeyFields(key_fields_);
}

const std::vector <std::string>& DBFileOut::getFieldNames() const
{
	return field_names_;
}
