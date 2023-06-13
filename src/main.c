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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#ifndef _WIN32
# include <libgen.h>
#endif /* !_WIN32 */
#include "scanner.h"

# define OPTARG_LONG_SEP_BASE "--"
# define OPTARG_SHORT_SEP_BASE "-"

#define IS_OPTARG_BASE(_a, _s, _l)				\
  strcmp(OPTARG_SHORT_SEP_BASE _s, _a) == 0		\
	|| strcmp(OPTARG_LONG_SEP_BASE _l, _a) == 0

#define IS_OPTARG_LONG_BASE(_a, _l) \
  strcmp(OPTARG_LONG_SEP_BASE _l, _a) == 0

#define IS_NOT_OPTARG_BASE(_a) _a[0] != '-'

#ifdef _WIN32
# define OPTARG_SHORT_SEP "/"
# define OPTARG_LONG_SEP "/"

# define IS_OPTARG(_a, _s, _l)						\
  IS_OPTARG_BASE(_a, _s, _l)						\
	   || strcmp(OPTARG_SHORT_SEP _s, _a) == 0		\
	|| strcmp(OPTARG_LONG_SEP _l, _a) == 0

# define IS_OPTARG_LONG(_a, _l)					\
  IS_OPTARG_LONG_BASE(_a, _l)					\
	   || strcmp(OPTARG_LONG_SEP _l, _a) == 0

# define IS_NOT_OPTARG(_a) IS_NOT_OPTARG_BASE(_a) && _a[0] != '/'

#else /* _WIN32 */
# define OPTARG_SHORT_SEP OPTARG_SHORT_SEP_BASE
# define OPTARG_LONG_SEP  OPTARG_LONG_SEP_BASE

# define IS_OPTARG IS_OPTARG_BASE
# define IS_OPTARG_LONG IS_OPTARG_LONG_BASE
# define IS_NOT_OPTARG IS_NOT_OPTARG_BASE
#endif /* _WIN32 */

#define OPTARG_HELP(_s, _l, _h) printf("\t" OPTARG_SHORT_SEP _s ", "	\
									   OPTARG_LONG_SEP _l "\t" _h "\n")

#define OPTARG_LONG_HELP(_l, _h) printf("\t" OPTARG_LONG_SEP _l \
										"\t" _h "\n")

#define OPTARG_HELP_VAL(_s, _l, _v, _h) printf("\t" OPTARG_SHORT_SEP _s ", " \
											   OPTARG_LONG_SEP _l " " _v "\t" \
											   _h "\n")

static char *prg_name;

void
show_usage(int retval)
{
  printf("Usage: %s [OPTION]... [FILE]...\n", prg_name);
  printf("Transpile PL/Stupid source file to Assembly\n\n");

  OPTARG_HELP_VAL("o", "out", "FILE", "");
  OPTARG_LONG_HELP("dump-ast", "output AST as json and exit");
  OPTARG_HELP("h", "help", "display this help and exit");
  OPTARG_LONG_HELP("version", "output version information and exit");

  printf("\nExamples:\n");
  printf("\t%s main.pls\tTranspile main.pls to main.s\n", prg_name);

  exit(retval);
}

void
show_version(void)
{
  printf("%s v0.0\n", prg_name);
  printf("Copyright (C) 2023 d0p1\n");
  printf("License BSD-3-Clause: <https://directory.fsf.org/wiki/License:BSD-3-Clause>\n");
  printf("This is free software: you are free to change and redistribute it.\n");
  printf("There is NO WARRANTY, to the extent permitted by law.\n");

  exit(EXIT_SUCCESS);
}

int
parse_flags(int argc, char *const argv[])
{
  int idx;
  
  for (idx = 0; idx < argc; idx++)
    {
      if (IS_OPTARG(argv[idx], "h", "help"))
		{
		  show_usage(EXIT_SUCCESS);
		}
	  else if (IS_OPTARG_LONG(argv[idx], "version"))
		{
		  show_version();
		}
	  else if (IS_OPTARG(argv[idx], "o", "out"))
		{
		  
		}
	  else if (IS_NOT_OPTARG(argv[idx]))
		{
		  break;
		}
	  else
		{
		  show_usage(EXIT_FAILURE);
		}
    }
  
  return (idx);
}

int
compile_single_file(char const *file)
{
  Scanner scanner;
  Token tok;
  FILE *fp;

  fp = fopen(file, "r");
  if (fp == NULL)
	{
	  fprintf(stderr, "%s: fatal error: %s: %s\n",
			  prg_name, file, strerror(errno));
	  exit(EXIT_FAILURE);
	}

  scanner = scanner_init(fp, file);
  /* First pass */
  while (scanner_scan(&scanner, &tok) != 0)
	{
	  printf("%s (l:%zu,c:%zu,s:%zu)\n", token_to_str(tok.token), tok.line, tok.col, tok.length);
	  if (tok.token == T_IDENT)
		{
		  printf("val: %s\n", tok.value.strval);
		}
	}
  
  scanner_reset(&scanner);
  /* Second pass */

  fclose(fp);
  return (0);
}

int
compile_files(int argc, char *const argv[])
{
  int idx;

  for (idx = 0; idx < argc; idx++)
	{
	  compile_single_file(argv[idx]);
	}

  return (0);
}

int
main(int argc, char *const argv[])
{
  int idx;

#ifndef _WIN32
  prg_name = basename(argv[0]);
#else /* !_WIN32 */
  prg_name = argv[0];
#endif /* !_WIN32 */
  idx = parse_flags(argc - 1, argv + 1);
  idx++; /* skip argv[0] :) */
  if (idx >= argc)
	{
	  fprintf(stderr, "%s: fatal error: no input files\n", prg_name);
	  return (EXIT_FAILURE);
	}

  compile_files(argc - idx, argv + idx);

  return (EXIT_SUCCESS);
}
