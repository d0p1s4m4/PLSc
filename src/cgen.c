#include <stddef.h>
#include <string.h>
#include "cgen.h"
#include "error.h"

extern char const *target_backend;

static Backend *targets[] = {
  &cgen_nasm,
  &cgen_gas,
  NULL
};

static Backend *selected = NULL;

void
cgen_init(void)
{
  int idx;

  for (idx = 0; targets[idx] != NULL; idx++)
	{
	  if (strcmp(targets[idx]->name, target_backend) == 0)
		{
		  selected = targets[idx];
		  break;
		}
	}

  if (selected == NULL)
	{
	  error_fatal("unknown target \"%s\"", target_backend);
	}
}
