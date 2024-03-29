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
#include "plsc.h"
#include "term.h"

void
term(FILE *stream, int effect)
{
  if (!colorize)
	{
	  return;
	}
  fprintf(stream, "\033[%dm", effect);
}

void
term_color_red(FILE *stream)
{
  if (!colorize)
	{
	  return;
	}
  fprintf(stream, "\033[31m");
}

void
term_color_magenta(FILE *stream)
{
  if (!colorize)
	{
	  return;
	}
  fprintf(stream, "\033[35m");
}

void
term_text_bold(FILE *stream)
{
  if (!colorize)
	{
	  return;
	}
  fprintf(stream, "\033[1m");
}

void
term_text_underline(FILE *stream)
{
  if (!colorize)
	{
	  return;
	}
  fprintf(stream, "\033[4m");
}

void
term_color_reset(FILE *stream)
{
  if (!colorize)
	{
	  return;
	}
  fprintf(stream, "\033[0m");
}

void
term_url(FILE *stream, char const *title, char const *url)
{
  if (!colorize)
	{
	  fprintf(stream, "%s", title);
	  return;
	}
  fprintf(stream, "\033]8;;%s\033\\%s\033]8;;\033\\", url, title);
}
