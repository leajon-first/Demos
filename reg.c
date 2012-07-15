/*
 * gcc reg.c -o reg -lpcre
 */
#include <stdio.h>
#include <string.h>
#include <pcre.h>

int is_match (const char *src, const char *pattern)
{
	pcre *re;
	const char *error;
	int erroffset;
	int result;

	re = pcre_compile (pattern,       /* the pattern */
			0,       /* default options */
			&error,       /* for error message */
			&erroffset, /* for error offset */
			NULL);       /* use default character tables */

	/* Compilation failed: print the error message and exit */
	if (re == NULL) {
		printf ("PCRE compilation failed at offset %d: %s\n", erroffset, error);
		return -1;
	}

	result = pcre_exec (re,        /* the compiled pattern */
			NULL, /* no extra data - we didn't study the pattern */
			src, /* the src string */
			strlen (src), /* the length of the src */
			0,        /* start at offset 0 in the src */
			0,        /* default options */
			NULL, 0);

	/* If Matching failed: */
	if (result < 0) {
		free (re);
		return -1;
	}

	free (re);
	return result;
}


	int
main ( int argc, char *argv[] )
{
	const char *pattern = "((25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d?\\d)";
	const char *src = "5250.222.0.12";

	int result = is_match (src ,pattern);
	printf ("result is: %d\n", result);
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
