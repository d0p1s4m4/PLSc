#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "plsc.h"
#include "token.h"
#include "term.h"

void
error_fatal(char const *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  term_text_bold(stderr);
  fprintf(stderr, "%s: ", prg_name);
  term_color_reset(stderr);
  term_color_red(stderr);
  fprintf(stderr, "fatal error: ");
  term_color_reset(stderr);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);

  exit(EXIT_FAILURE);
}

void
error_tok(Token *tok)
{
  term_text_bold(stderr);
  fprintf(stderr, "%s:%lu:%lu: ", tok->file, (unsigned long)tok->line,
		  (unsigned long)tok->col);
  term_color_reset(stderr);
  term_color_red(stderr);
  fprintf(stderr, "error: ");
  term_color_reset(stderr);

  fprintf(stderr, " stray ");
  term_text_bold(stderr);
  fprintf(stderr, "'%c' ", (char)tok->value.intval);
  term_color_reset(stderr);
  fprintf(stderr, "in program\n");
  fprintf(stderr, " %5lu | %s\n", (unsigned long)tok->line, tok->linebuffer);
  fprintf(stderr, "       | ");

  term_color_red(stderr);
  fprintf(stderr, "%*c\n", (int)tok->col, '^');
  term_color_reset(stderr);
}
