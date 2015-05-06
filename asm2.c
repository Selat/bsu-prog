#include <stdio.h>
#include <string.h>

#define MYMACRO(N) int name##N = 5;

int countWords(char *s)
{
	char prev = ' ';
	int num = 0;
	while(*s != '\0') {
		if((*s != ' ') && (prev == ' ')) {
			++num;
		}
		prev = *s;
		++s;
	}
	return num;
}

int countWordsAsm(char *s)
{
	__asm__ volatile(
		"mov rbx, %0\n"
		"xor eax, eax\n"
		"xor ecx, ecx\n"
		"mov edx, 32\n"
		"l1: mov cl, [rbx]\n"
		"cmp cl, 0\n"
		"je end\n"

		"cmp dl, 32\n"
		"jne s1\n"
		"cmp cl, 32\n"
		"je s1\n"
		"inc eax\n"

		"s1: "
		"mov dl, [rbx]\n"
		"inc rbx\n"
		"jmp l1\n"

		"end:"
		:
		: "g" (s)
		);
}

int main()
{
	char buf[256];
	int words_num, words_num_asm;
	fgets(buf, 256, stdin);
	words_num_asm = countWordsAsm(buf);
	words_num = countWords(buf);
	printf("Words num: %d (by assembly) %d (by C++)\n", words_num_asm, words_num);
	return 0;
}
