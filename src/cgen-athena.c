#include <stdio.h>
#include "cgen.h"

void
cgen_athena_function(FILE *stream, char const *name)
{
  fprintf(stream,
		  "%s:\n"
		  "\tsubi sp, sp, 16\n",
		  name);

  fprintf(stream,
		  "\taddi sp, sp, 16\n"
		  "\tjr ra\n");
}

CGEN_BACKEND(athena);
