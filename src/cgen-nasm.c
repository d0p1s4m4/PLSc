#include <stdio.h>
#include "cgen.h"

static int free_registers[3];

static char *register_names[] =
  {
	/* scratch registers */
	"eax", "ecx", "edx",

	/* preserved registers */
	"ebx", "esi", "edi",

	/*"xmm0", "xmm1", "xmm2", "xmm3",
	  "xmm4", "xmm5", "xmm6", "xmm7"*/
  };

static char *register16_names[] =
  {
	"ax", "cx", "dx",

	"bx", "si", "di",
  };

static char *register8_names[] =
  {
	"al", "cl", "dl",
	"bl"
  };

void
cgen_nasm_function(FILE *stream, char const *name)
{
  (void)free_registers;
  (void)register_names;
  (void)register16_names;
  (void)register8_names;
  fprintf(stream,
		  "%s:\n"
		  "\tpush esp\n"
		  "\tmov ebp, esp\n",
		  name);

  fprintf(stream, "\tleave\nret\n");
}

CGEN_BACKEND(nasm);
