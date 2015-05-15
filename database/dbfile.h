#ifndef DBFILE_H
#define DBFILE_H

#include <vector>
#include <fstream>
#include <string>

#include "dbfield.h"
#include "dbkey.h"

class DBFile
{
public:
	DBFile(DBFile&& file);
	DBFile(const std::string &filename, int fields_num);
	bool open();
	void close();
	bool readNextEntry();
	const std::vector <DBField>& getCurrentEntry();
	DBKey getCurrentKey();

	void setFieldNames(const std::initializer_list<std::string> &names);
	void setKeyFields(const std::initializer_list<int> &l);

	const std::vector <std::string>& getFieldNames();

protected:
	std::string filename_;
	std::ifstream file_;
	std::vector <std::string> field_names_;
	std::vector <DBField> entry_;
	std::vector <int> key_fields_;
};

#endif
