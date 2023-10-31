#include <stddef.h>
#include <stdio.h>
#include "cgen.h"

static char *register_names[] =
  {
	"%eax", "%ebx", "%ecx", "%edx",
	"%esp", "%ebp", "%esi", "%edi",

	"%xmm0", "%xmm1", "%xmm2", "%xmm3",
	"%xmm4", "%xmm5", "%xmm6", "%xmm7"
  };

static char *register16_names[] =
  {
	"%ax", "%bx", "%cx", "%dx",
	"%sp", "%bp", "%si", "%di",

	NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL
  };

void
cgen_gas_function(FILE *stream, char const *name)
{
  (void)register_names;
  (void)register16_names;
  fprintf(stream,
		  "%s:\n"
		  "\tpushl %%ebp\n"
		  "\tmovl %%esp, %%ebp\n",
		  name);

  fprintf(stream, "\tleave\n\ret\n");
}

void
cgen_gas_init(FILE *stream, const char *fname)
{
  fprintf(stream,
		  "\t.file \"%s\"\n"
		  "\t.text\n", fname);
}

CGEN_BACKEND(gas);
