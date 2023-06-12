#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

# define OPTARG_LONG_SEP_BASE "--"
# define OPTARG_SHORT_SEP_BASE "-"

#define IS_OPTARG_BASE(_a, _s, _l)				\
  strcmp(OPTARG_SHORT_SEP_BASE _s, _a) == 0		\
	|| strcmp(OPTARG_LONG_SEP_BASE _l, _a) == 0

#define IS_OPTARG_LONG_BASE(_a, _l) \
  strcmp(OPTARG_LONG_SEP_BASE _l, _a) == 0

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

#else /* _WIN32 */
# define OPTARG_SHORT_SEP OPTARG_SHORT_SEP_BASE
# define OPTARG_LONG_SEP  OPTARG_LONG_SEP_BASE

# define IS_OPTARG IS_OPTARG_BASE
# define IS_OPTARG_LONG IS_OPTARG_LONG_BASE
#endif /* _WIN32 */

#define OPTARG_HELP(_s, _l, _h) printf("\t" OPTARG_SHORT_SEP _s ", "	\
									   OPTARG_LONG_SEP _l "\t" _h "\n")

#define OPTARG_LONG_HELP(_l, _h) printf("\t" OPTARG_LONG_SEP _l \
										"\t" _h "\n")

static char *prg_name;

void
show_usage(int retval)
{
  printf("Usage: %s [OPTION]... [FILE]...\n", prg_name);
  printf("Transpile PL/Stupid source file to Assembly\n\n");

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
    }
  
  return (EXIT_FAILURE);
}

int
main(int argc, char *const argv[])
{
  prg_name = basename(argv[0]);
  return (parse_flags(argc - 1, argv + 1));
}

