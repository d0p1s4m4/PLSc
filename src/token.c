#include "token.h"

static char *token_str[] = {
  "(", ")", ":", ";", ",", ".", "-", "+", "*", "<<", ">>", ">", "<",
  "==", "<=", ">=", "(number)", "(char)", "(str)", "IDENT"
};

const char *
token_to_str(TokenType type)
{
  return token_str[type];
}
