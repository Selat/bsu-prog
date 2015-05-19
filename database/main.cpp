#include <iostream>

#include "dbfile.h"
#include "dbiterator.h"

using namespace std;

int main()
{
	DBFile file1("db1.txt", 2);
	DBFile file2("db2.txt", 3);
	DBFile file3("db3.txt", 4);
	std::vector<DBFile*> files = {&file1, &file2, &file3};
	file1.setKeyFields({0});
	file2.setKeyFields({0, 1});
	file3.setKeyFields({0, 1, 2});
	DBIterator it(files);
	it.init();
	while(it.nextEntry()) {
		for(int i = 0; i < it.getCurrentEntry().size(); ++i) {
			cout << it.getCurrentEntry()[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
