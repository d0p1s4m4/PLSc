#ifndef ERROR_H
# define ERROR_H

# include <stdarg.h>

struct token;

typedef enum
  {
	E_STRAY,
	E_COMMENT_EOF,
	E_STR_EOF,

	E_UNKNOWN
  } Error;

void error_fatal(char const *fmt, ...);
void error_tok(struct token *tok);

#endif /* !ERROR_H */

