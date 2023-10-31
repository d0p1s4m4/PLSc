#include <stddef.h>
#include <stdio.h>
#include "cgen.h"

void
cgen_c_function(FILE *stream, char const *name)
{
  (void)register_names;
  (void)register16_names;
  fprintf(stream,
		  "%s() {\n"
		  name);

  fprintf(stream, "\n}\n");
}

CGEN_BACKEND(c);
