#include <stdlib.h>
#include "term.h"

void
term_color_red(FILE *stream)
{
  char *no_color;

  no_color = getenv("NO_COLOR");

  if (no_color != NULL && no_color[0] != '\0')
	{
	  return;
	}

  fprintf(stream, "\033[31m");
}

void
term_color_reset(FILE *stream)
{
  fprintf(stream, "\033[0m");
}
