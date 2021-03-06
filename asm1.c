#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

/*
 * The task is to calculate the following function:
 * D(n, m) = \dfrac{(5n)!(5m)!}
 *             {n!m!(3n + m)!(3m + n)!}
 */

int FPower(int x, int n)
{
	__asm__ volatile (
		".intel_syntax noprefix;\n"
		"mov eax, 1\n"
		"mov ecx, %1\n"
		"mov ebx, %0\n"
		"loop1: jecxz end_pow\n"
		"shr ecx, 1\n"
		"jnc skip1\n"
		"imul eax, ebx\n"
		"skip1: imul ebx, ebx\n"
		"jmp loop1\n"
		"end_pow:"
		:
		: "r" (x), "r" (n)
		);
}

int sum(int n, int m)
{
	int res = 0;
	volatile int test = n;
	__asm__ volatile(
		".intel_syntax noprefix;\n"
		"mov eax,  %1\n"
		"imul ebx, eax, 2\n"
		"mov %0, ebx\n"
		: "=r" (res)
		: "r" (m));
	printf("%d\n", res);
	return res;
}

int gcd(uint64_t a, uint64_t b)
{
	while((a %= b) && (b %= a));
	return a|b;
}

/* This function caculates function up to D(2, 2) */
uint64_t calc1(int n, int m)
{
	float v1[] = {1.0f, 2.0f, 3.0f, 4.0f};
	float v2[] = {2.0f, 3.0f, 4.0f, 5.0f};
	float v3[] = {1.0f, 2.0f, 3.0f, 4.0f};
	uint64_t tmp[] = {1, 2};
	uint64_t total[] = {3, 4};
	uint64_t res[] = {1, 2};
	unsigned a = 5;
	unsigned b = 6;
	uint32_t test = a * b * 678u;
	__asm__ volatile(
		".intel_syntax noprefix;\n"
		/* find out the maximum of n and m */
		"movd xmm0, %3\n"
		"movd xmm1, %4\n"
		"pmaxud xmm0, xmm1\n"
		"movd eax, xmm0\n"
		"movd ecx, xmm0\n"
		"mov ecx, 1\n"

		"sub rsp, 16\n"

		/* perform min(n, m) iterations and calculate D(n, m) */
		/* D(n, m) = D(n - 1, m - 1) * ((5 * n) * (5 * n - 1) * (5 * n - 2) * (5 * n - 3) * (5 * n - 4) /            */
		/* / (n * (3 * n + m) * (3 * n + m - 1) * (3 * n + m - 2) * (3 * n + m - 3) * (3 * n + m - 4))) *            */
		/* ((5 * m) * (5 * m - 1) * (5 * m - 2) * (5 * m - 3) * (5 * m - 4) /                                        */
		/* / (m * (3 * m + n) * (3 * m + n - 1) * (3 * m + n - 2) * (3 * m + n - 3) * (3 * m + n - 4)))              */
		/* Fill registers with the following initial values
		   +-----+-----+-----+
		   |XMM0 |  1  |  1  |
		   +-----+-----+-----+
		   |XMM1 |  1  |  1  |
		   +-----+-----+-----+
		   |XMM2 |  1  |  1  |
		   +-----+-----+-----+
		   |XMM3 |  1  |  1  |
		   +-----+-----+-----+
		   |XMM4 | 4*n |  0  |
		   +-----+-----+-----+
		   |XMM5 | 3*n | 3*m |
		   +-----+-----+-----+
		   |XMM6 |  1  |  1  |
		   +-----+-----+-----+

		   What we are going to calculate:
		   +-----+---------------+----------------+
		   |XMM0 |  (5n!)/(4n!)  |        n!      |
		   +-----+---------------+----------------+
		   |XMM1 |  (4n!)/(3n!)  |  (3m+n)/(3m!)  |
		   +-----+---------------+----------------+
		   |XMM0 |  (5m!)/(4m!)  |        m!      |
		   +-----+---------------+----------------+
		   |XMM1 |  (4m!)/(3m!)  |  (3n+m)/(3n!)  |
		   +-----+---------------+----------------+
		*/
		"mov [rsp], dword ptr 1\n"
		"mov [rsp + 8], dword ptr 1\n"
		"movdqa xmm0, [rsp]\n"
		"movdqa xmm1, [rsp]\n"
		"movdqa xmm2, [rsp]\n"
		"movdqa xmm3, [rsp]\n"
		"movdqa xmm6, [rsp]\n"

		/* Fill xmm4 */
		"mov [rsp], dword ptr 0\n"
		"xor rax, rax\n"
		"mov eax, %3\n"
		"mov ebx, 4\n"
		"mul ebx\n"
		"mov [rsp + 8], rax\n"
		"movdqa xmm4, [rsp]\n"

		/* Fill xmm5 */
		"xor rax, rax\n"
		"mov eax, %4\n"
		"mov ebx, 3\n"
		"mul ebx\n"
		"mov [rsp], rax\n"
		"xor rax, rax\n"
		"mov eax, %3\n"
		"mul ebx\n"
		"mov [rsp + 8], rax\n"
		"movdqa xmm5, [rsp]\n"

		/* Perform n multiplications */
		"mov ecx, %3\n"
		"iter1:\n"
		"paddq xmm4, xmm6\n"
		"paddq xmm5, xmm6\n"
		"pmuludq xmm0, xmm4\n"
		"pmuludq xmm1, xmm5\n"
		"loop iter1\n"
		"movd rax, xmm0\n"

		/* Fill xmm4 */
		"mov [rsp], dword ptr 0\n"
		"xor rax, rax\n"
		"mov eax, %4\n"
		"mov ebx, 4\n"
		"mul ebx\n"
		"mov [rsp + 8], rax\n"
		"movdqa xmm4, [rsp]\n"

		/* Fill xmm5 */
		"xor rax, rax\n"
		"mov eax, %3\n"
		"mov ebx, 3\n"
		"mul ebx\n"
		"mov [rsp], rax\n"
		"xor rax, rax\n"
		"mov eax, %4\n"
		"mul ebx\n"
		"mov [rsp + 8], rax\n"
		"movdqa xmm5, [rsp]\n"

		/* Perform m multiplications */
		"mov ecx, %4\n"
		"iter2:\n"
		"paddq xmm4, xmm6\n"
		"paddq xmm5, xmm6\n"
		"pmuludq xmm2, xmm4\n"
		"pmuludq xmm3, xmm5\n"
		"loop iter2\n"
		"movq rax, xmm2\n"

		/* Final calculation of numerator and denominator*/
		"pmuludq xmm0, xmm1\n"
		"pmuludq xmm0, xmm2\n"
		"pmuludq xmm0, xmm3\n"

		/* Calculation the resulting D(n, m) */
		"movdqa [rsp], xmm0\n"
		"mov rax, [rsp + 8]\n"
		"mov rbx, [rsp]\n"
//		"div rax, rbx\n"
		"add rsp, 16\n"
		: "=g" (res)
		: "g" (tmp), "g" (total), "g" (n), "g" (m)
		);
}

/* This function caculates function up to D(6, 6) */
uint64_t calc2(int n, int m)
{
	__asm__ volatile (
		/*
		 * Registers use:
		 * rbx = a
		 * rdi = b
		 * rsi = D(n, m)
		 * D(n, m) = D(n, m - 1) * a / b or D(n, 0) = D(n - 1, 0) * a / b
		 */
		"mov rsi, 1\n"

		/* Calculate D(n, 0) */
		"mov rcx, 1\n"
		"d_n_0_calc: cmp ecx, %0\n"
		"jg d_n_0_end\n"

		/* Calculate nominator in rbx */
		"mov rbx, 1\n"
		"mov rax, rcx\n"
		"imul rax, 5\n"
		"mov r8, rcx\n"
		"mov rcx, 5\n"
		"d_n_0_nom:"
		"imul rbx, rax\n"
		"dec rax\n"
		"loop d_n_0_nom\n"
		"mov rcx, r8\n"

		/* Calculate denominator in rdi */
		"mov rdi, rcx\n"
		"imul rdi, rcx\n"
		"mov rax, rcx\n"
		"imul rax, 3\n"
		"mov r8, rcx\n"
		"mov rcx, 3\n"
		"d_n_0_denom: "
		"imul rdi, rax\n"
		"dec rax\n"
		"loop d_n_0_denom\n"
		"mov rcx, r8\n"

		/*
		 * Calculate D(n, 0) = D(n - 1, 0) * rbx / rdi
		 * TODO: Divide rbx and rdi by gcd(rbx, rdi) to prevent integer overflows.
		 */
		"mov rax, rsi\n"
		"imul rax, rbx\n"
		"xor rdx, rdx\n"
		"div rdi\n"
		"mov rsi, rax\n"

		"inc ecx\n"
		"jmp d_n_0_calc\n"
		"d_n_0_end: "

		/* Calculate D(n, m) (now we now the value of D(n, 0) */
		"mov rcx, 1\n"
		"d_n_m_calc: cmp ecx, %1\n"
		"jg d_n_m_end\n"

		/* Calculate nominator in rbx */
		"mov rbx, 1\n"
		"mov rax, rcx\n"
		"imul rax, 5\n"
		"mov r8, rcx\n"
		"mov rcx, 5\n"
		"d_n_m_nom:"
		"imul rbx, rax\n"
		"dec rax\n"
		"loop d_n_m_nom\n"
		"mov rcx, r8\n"

		/* Calculate denominator in rdi: m * (3n + m) * (3m + n) * (3m + n - 1) * (3m + n - 2)*/
		"mov rdi, rcx\n"
		"mov eax, %0\n"
		"imul rax, 3\n"
		"add rax, rcx\n"
		"imul rdi, rax\n"
		"mov rax, rcx\n"
		"imul rax, 3\n"
		"add eax, %0\n"
		"mov r8, rcx\n"
		"mov rcx, 3\n"
		"d_n_m_denom: "
		"imul rdi, rax\n"
		"dec rax\n"
		"loop d_n_m_denom\n"
		"mov rcx, r8\n"

		/*
		 * Calculate D(n, m) = D(n, m - 1) * rbx / rdi
		 * TODO: Divide rbx and rdi by gcd(rbx, rdi) to prevent integer overflows.
		 */

		"mov rax, rsi\n"
		"imul rax, rbx\n"
		"xor rdx, rdx\n"
		"div rdi\n"
		"mov rsi, rax\n"

		"inc ecx\n"
		"jmp d_n_m_calc\n"
		"d_n_m_end: "
		"mov rax, rsi\n"
		:
		: "g" (n), "g" (m)
		);
}

int calc3(int n, int m)
{
	int i;
	long long int nom = 1, denom = 1;
	for(i = 3 * n + 1; i <= 5 * n; ++i) {
		nom *= i;
	}
	for(i = 3 * m + 1; i <= 5 * m; ++i) {
		nom *= i;
	}
	for(i = 1; i <= n; ++i) {
		denom *= i;
	}
	for(i = 1; i <= m; ++i) {
		denom *= i;
	}
	for(i = 3 * n + 1; i <= 3 * n + m; ++i) {
		denom *= i;
	}
	for(i = 3 * m + 1; i <= n + 3 * m; ++i) {
		denom *= i;
	}
	return nom;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	printf("%llu\n", calc2(n, m));
	return 0;
}
