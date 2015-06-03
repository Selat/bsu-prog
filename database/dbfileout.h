#ifndef DBFILEOUT_H
#define DBFILEOUT_H

#include <vector>
#include <fstream>
#include <string>

#include "dbfield.h"
#include "dbkey.h"
#include "dbrecord.h"

class DBFileOut
{
public:
	DBFileOut(DBFileOut&& file);
	DBFileOut(const std::string &filename, int fields_num);
	bool open();
	void close();
	bool writeEntry();

	DBRecord& getCurrentEntry();
	DBKey getCurrentKey() const;
	void setCurrentKey(const DBKey &k);

	void setFieldNames(const std::initializer_list<std::string> &names);
	void setKeyFields(const std::initializer_list<int> &l);

	const std::vector <std::string>& getFieldNames() const;

protected:
	std::string filename_;
	std::ofstream file_;
	std::vector <std::string> field_names_;
	DBRecord entry_;
	std::vector <int> key_fields_;
};

#endif
