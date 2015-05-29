#include <iostream>
#include <cstring>
#include <cassert>

#define VAL(ID) ID

#define TESTCASE(ID, IN, OUT) \
	char str ## ID [] = IN; \
	char str ## ID ## _ans[] = OUT; \
	solve(str ## ID); \
	int res ## ID = strcmp(str ## ID, str ## ID ## _ans); \
	assert(res ## ID == 0);	\

using namespace std;

/*
 * On input function "solve" recieves null-terminated string, which consists of
 * alphabetic symbols, spaces and symbol ';'.
 * The task is to left only one space between any two words, and exactly one symbol
 * after each ';' - it constitues for the end of the sentence.
 */

extern "C" int solve(char *s);

void runTests()
{
	// TESTCASE(1, "   1    23   3    5     ", "1 23 3 5");
	// TESTCASE(2, "      1 23   3    5", "1 23 3 5");
	// TESTCASE(3, "1       23   3    5", "1 23 3 5");
	// TESTCASE(4, "1 23         3    5", "1 23 3 5");
	// TESTCASE(5, "1 23 3            5", "1 23 3 5");
	// TESTCASE(6, "1 23 3 5           ", "1 23 3 5")
	// TESTCASE(7, "1 23 3 5", "1 23 3 5");
	// TESTCASE(8, " 1 23 3 5", "1 23 3 5");
	// TESTCASE(9, "1  23 3 5", "1 23 3 5");
	// TESTCASE(10, "1  23 3 5 ", "1 23 3 5");
}

int main()
{
	runTests();
	char buf[256];
	fgets(buf, 256, stdin);
	buf[strlen(buf) - 1] = '\0';
	int id = solve(buf);
	printf("%s %d\n", buf, id);
	return 0;
}
