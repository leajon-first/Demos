/*
 *gcc regex.c -o regex
 */
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
/*
 * Regular expressions  verification
 * If matched success: return 0
 */
int is_match(const char *src, const char *pattern)
{
	regex_t preg;
	char prbuf[200];
	int rc;

	rc = regcomp(&preg, pattern, REG_EXTENDED);
	if (rc != 0) {
		regerror(rc, &preg, prbuf, sizeof(prbuf));
		printf("Regex compile error: %s\n", prbuf);
	}
	rc = regexec(&preg, src, 0, 0,  0);
	return rc;
}
	int
main ( int argc, char *argv[] )
{
	const char *pattern = "^((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])$";
	const char *src = "5250.222.0.12";
	const char *src1 = "127.0.0.1";
	int result = is_match(src, pattern);
	printf ("%s %s\n", src, result != 0? "not matched":"matched");
	result = is_match(src1, pattern);
	printf ("%s %s\n", src1, result != 0? "not matched":"matched");
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
