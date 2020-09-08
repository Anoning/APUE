/*
 *	use the setvbuf function to realize the setbuf function
 *	step: size = BUFSIZ
 *	      1) if buf==NULL, set mode = _IONBF
 *	      2) if buf!=NULL, a) normal file , mode = _IOFBF	
 *			       b) tty, mode = _IOLBF
 */
#include "apue.h"
#include <error.c>

bool is_tty(FILE *stream){
	return isatty(fileno(stream));
}

void my_setbuf(FILE *stream, char *buf)
{
	if(buf == NULL) 
		setvbuf(stream, buf, _IONBF, BUFSIZ);
	else if(is_tty(stream)){
		setvbuf(stream, buf, _IOLBF, BUFSIZ);
	}
	else{
		setvbuf(stream, buf, _IOFBF, BUFSIZ);
	}
}

