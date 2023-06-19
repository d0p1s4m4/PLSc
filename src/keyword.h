#ifndef KEYWORD_H
# define KEYWORD_H 1

# include "token.h"

typedef struct
{
  char const *str;
  TokenType token;
} Keyword;

extern Keyword keywords[];

#endif /* !KEYWORD_H */
