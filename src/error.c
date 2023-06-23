/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2023, d0p1
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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

static void
stray_char(Token *tok)
{
  fprintf(stderr, "stray ");
  term_text_bold(stderr);
  fprintf(stderr, "'%c' ", (char)tok->error.c);
  term_color_reset(stderr);
  fprintf(stderr, "in program\n");
}

static void
number_suffix(Token *tok)
{
  fprintf(stderr, "invalid suffix ");
  term_text_bold(stderr);
  fprintf(stderr, "\"%s\" ", tok->error.str);
  term_color_reset(stderr);
  fprintf(stderr, "on integer constant\n");
}

void
error_tok(Token *tok)
{
  int idx;

  term_text_bold(stderr);
  fprintf(stderr, "%s:%lu:%lu: ", tok->file, (unsigned long)tok->line,
		  (unsigned long)tok->col);
  term_color_reset(stderr);
  term_color_red(stderr);
  fprintf(stderr, "error: ");
  term_color_reset(stderr);

  switch (tok->error.type)
	{
	case E_STRAY:
	  stray_char(tok);
	  break;
	case E_NUMBER_SUFFIX:
	  number_suffix(tok);
	  break;
	default:
	  error_fatal("unknown error ");
	  break;
	}

  fprintf(stderr, " %5lu | %s\n", (unsigned long)tok->line, tok->linebuffer);
  fprintf(stderr, "       | ");

  term_color_red(stderr);
  fprintf(stderr, "%*c", (int)tok->col, '^');
  for (idx = 1; idx < (int)tok->length; idx++)
	{
	  fprintf(stderr, "~");
	}
  fprintf(stderr, "\n");
  term_color_reset(stderr);
}
