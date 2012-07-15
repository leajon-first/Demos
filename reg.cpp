/*
 * g++ reg.cpp -o regcpp -lpcre
 */
#include	<iostream>
#include	<string.h>
#include	<pcre.h>

bool is_match(const char *src, const char *pattern);
bool is_ipaddr_legal(const char *src);
bool is_hostname_legal(const char *src);

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_match
 *  Description:  true for match successful.
 * =====================================================================================
 */
	bool
is_match ( const char *src, const char *pattern )
{
	pcre *re;
	const char *error;
	int erroffset;
	int result;

	re = pcre_compile (pattern,             /* the pattern */
			0,                      /* default options */
			&error,                 /* for error message */
			&erroffset,             /* for error offset */
			NULL);                  /* use default character tables */

	/* Compilation failed: print the error message and exit */
	if (re == NULL) {
		std::cout << "PCRE compilation failed at offset" <<  erroffset <<  error << std::endl;
		return -1;
	}

	result = pcre_exec (re,			/* the compiled pattern */
			NULL,			/* no extra data - we didn't study the pattern */
			src,			/* the src string */
			strlen (src),		/* the length of the src */
			0,			/* start at offset 0 in the src */
			0,			/* default options */
			NULL, 0);

	/* If Matching failed: */
	if (result < 0) {
		free (re);
		return false;
	}
	else {
		free (re);
		return true;
	}

}		/* -----  end of function is_match  ----- */



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_ip_addr_legal
 *  Description:  legal:true    illegal:false
 * =====================================================================================
 */
	bool
is_ipaddr_legal ( const char *src )
{
	const char *pattern = "^((25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d?\\d)$";
	return is_match(src, pattern);
}		/* -----  end of function is_ip_addr_legal  ----- */



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_hostname_legal
 *  Description:  legal:true    illegal:false
 * =====================================================================================
 */
	bool
is_hostname_legal ( const char *src )
{
	const char *pattern = "^[a-zA-Z][a-zA-Z0-9_]{5,30}$";
	return is_match(src, pattern);
}		/* -----  end of function is_hostname_legal  ----- */



	int
main ( int argc, char *argv[] )
{
	const char *src = "250.222.0.12";
	const char *src1 = "558.247.250.223";
	const char *src2 = "asdfaf00098_";
	const char *src3 = "&*^%*&^0009808qwefasd";
	const char *src4 = "0000_234";

	std::cout << src << '\t'<< (is_ipaddr_legal(src)? "true":"false") << std::endl;
	std::cout << src1 << '\t'<< (is_ipaddr_legal(src1)? "true":"false") << std::endl;
	std::cout << src2 << '\t'<< (is_hostname_legal(src2)? "true":"false") << std::endl;
	std::cout << src3 << '\t'<< (is_hostname_legal(src3)? "true":"false") << std::endl;
	std::cout << src4 << '\t'<< (is_hostname_legal(src4)? "true":"false") << std::endl;

	return 0;
}				/* -----c----  end of function main  ---------- */
