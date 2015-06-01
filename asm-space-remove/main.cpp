#include <iostream>
#include <cstring>
#include <cassert>

#define TESTCASE(IN, OUT)	  \
	do{ \
		char str [] = IN; \
		char str_ans[] = OUT; \
		solve(str); \
		int res = strcmp(str, str_ans); \
		assert(res == 0); \
	}while(0)

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
	// Testing just space removing
	TESTCASE("1 25     ", "1 25");
	TESTCASE("   1    23   3    5     ", "1 23 3 5");
	TESTCASE("   1    23   3    5     ", "1 23 3 5");
	TESTCASE("      1 23   3    5", "1 23 3 5");
	TESTCASE("1       23   3    5", "1 23 3 5");
	TESTCASE("1 23         3    5", "1 23 3 5");
	TESTCASE("1 23 3            5", "1 23 3 5");
	TESTCASE("1 23 3 5           ", "1 23 3 5");
	TESTCASE("1 23 3 5", "1 23 3 5");
	TESTCASE(" 1 23 3 5", "1 23 3 5");
	TESTCASE("1  23 3 5", "1 23 3 5");
	TESTCASE("1  23 3 5 ", "1 23 3 5");
	TESTCASE("1 2 2  ", "1 2 2");
	TESTCASE("", "");
	TESTCASE("               ", "");
	// Testing space removing and addition of space after each semicolon
	TESTCASE("1  ;", "1 ; ");
	TESTCASE("  1;", "1; ");
	TESTCASE("1   ;2", "1 ; 2");
	TESTCASE("2  1;", "2 1; ");
	TESTCASE(" ;", "; ");
	TESTCASE("          ;;;;;;;;;;", "; ; ; ; ; ; ; ; ; ; ");
	puts("The program successfully passed all testcases!");
}

int main()
{
	runTests();
	char buf[256];
	fgets(buf, 256, stdin);
	buf[strlen(buf) - 1] = '\0';
	int n = solve(buf);
	printf("%s|%d\n", buf, n);
	return 0;
}
