#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define IS_OPTARG_BASE(_a, _s, _l) _a[0] == '-' \
				    && (_a[1] == _s \
					|| strcmp(_a + 1, "-" _l) == 0)
#ifdef _WIN32
# define IS_OPTARG(_a, _s, _l) (IS_OPTARG_BASE(_a, _s, _l)) \
				|| (_a[0] == '/' \
				    && (_a[1] == _s \
					|| strcmp(_a + 1, _l) == 0))
#else
# define IS_OPTARG IS_OPTARG_BASE
#endif

int
parse_flags(int argc, char *const argv[])
{
  int idx;

  for (idx = 0; idx < argc; idx++)
    {
      if (IS_OPTARG(argv[idx], 'h', "help"))
	{
	  printf("Help\n");
	  exit(EXIT_SUCCESS);
	}
    }

  return (EXIT_FAILURE);
}

int
main(int argc, char *const argv[])
{
  return (parse_flags(argc - 1, argv + 1));
}

