#include <iostream>
#include <cstring>

using namespace std;

/*
 * On input function "solve" recieves null-terminated string, which consists of
 * alphabetic symbols, spaces and symbol ';'.
 * The task is to left only one space between any two words, and exactly one symbol
 * after each ';' - it constitues for the end of the sentence.
 */

extern "C" int solve(char *s);

int main()
{
	char buf[256];
	fgets(buf, 256, stdin);
	buf[strlen(buf) - 1] = '\0';
	int id = solve(buf);
	printf("%s %d\n", buf, id);
	return 0;
}
