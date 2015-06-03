#ifndef DBFILEIN_H
#define DBFILEIN_H

#include <vector>
#include <fstream>
#include <string>

#include "dbfield.h"
#include "dbkey.h"
#include "dbrecord.h"

class DBFileIn
{
public:
	DBFileIn(DBFileIn&& file);
	DBFileIn(const std::string &filename, int fields_num);
	bool open();
	void close();
	bool eof() const;
	bool readNextEntry();

	const DBRecord& getCurrentEntry() const;
	DBKey getCurrentKey() const;

	void setFieldNames(const std::initializer_list<std::string> &names);
	void setKeyFields(const std::initializer_list<int> &l);

	const std::vector <std::string>& getFieldNames() const;

protected:
	std::string filename_;
	std::ifstream file_;
	std::vector <std::string> field_names_;
	DBRecord entry_;
	std::vector <int> key_fields_;
};

#endif
