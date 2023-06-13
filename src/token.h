#ifndef TOKEN_H
# define TOKEN_H 1

# include <stddef.h>
# include <stdint.h>

typedef enum {
  T_LPAREN,
  T_RPAREN,
  T_COLON,
  T_SEMICOLON,
  T_COMMA,
  T_DOT,
  T_MINUS,
  T_PLUS,
  T_ASTERISK,
  T_LSHIFT,
  T_RSHIFT,
  T_GREATER,
  T_LESSER,

  T_EQUAL_EQUAL,
  T_LESSER_EQUAL,
  T_GREATER_EQUAL,

  T_NUMBER,
  T_CHAR,
  T_STRING,

  T_IDENT,

  /* keyword */
  T_PROC,
  T_ENTRY,
  T_DCL,
  T_DO,
  T_END,

  T_EOF,
  T_MAX
} TokenType;

typedef struct {
  TokenType token;

  /* usefull for error reporting  */
  size_t length;
  size_t line;
  size_t col;

  char *linebuffer;

  /* raw val */
  union value
  {
	unsigned uintval;
    int intval;
	char *strval;
  } value;
} Token;

const char *token_to_str(TokenType type);

#endif /* !TOKEN_H */
