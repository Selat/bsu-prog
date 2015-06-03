#include <iostream>

#include "dbfilein.h"
#include "dbfileout.h"
#include "dbiterator.h"

using namespace std;

int main()
{
	DBFileIn file1("db1.txt", 2);
	DBFileIn file2("db2.txt", 3);
	DBFileIn file3("db3.txt", 4);
	std::vector<DBFileIn*> files = {&file1, &file2, &file3};
	file1.setKeyFields({0});
	file2.setKeyFields({0, 1});
	file3.setKeyFields({0, 1, 2});
	file1.open();
	file2.open();
	file3.open();
	file1.readNextEntry();
	file2.readNextEntry();
	file3.readNextEntry();
	DBFileOut fout("dbres.txt", 6);
	fout.setKeyFields({0, 1, 2});
	fout.open();
	bool used[3];
	used[0] = used[1] = used[2] = false;
	bool running = true;
	// DBIterator it(files);
	// it.init();
	while(running) {
		for(size_t i = 0; i < 2; ++i) {
			if(!used[i] && (files[i]->getCurrentKey() != files[2]->getCurrentKey())) {
				cerr << "Unmatched keys: " << files[i]->getCurrentEntry() << " and " << files[2]->getCurrentEntry() << endl;
				running = false;
				break;
			} else if(used[i] && (files[i]->getCurrentKey() != files[2]->getCurrentKey())) {
				files[i]->readNextEntry();
			}
			if(files[i]->eof()) {
				cerr << "File ended: " << i << endl;
				running = false;
				break;
			}
		}
		if(!running) {
			break;
		}

		fout.setCurrentKey(file3.getCurrentKey());
		fout.getCurrentEntry()[3] = file1.getCurrentEntry()[1];
		fout.getCurrentEntry()[4] = file2.getCurrentEntry()[2];
		fout.getCurrentEntry()[5] = file3.getCurrentEntry()[3];

		if(!fout.writeEntry()) {
			cerr << "Write error!" << endl;
			running = false;
			break;
		}
		if(!file3.readNextEntry()) {
			running = false;
			break;
		}
		used[2] = false;
		used[1] = true;
		used[0] = true;
	}
	return 0;
}
