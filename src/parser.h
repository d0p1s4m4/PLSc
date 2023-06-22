#ifndef PARSER_H
# define PARSER_H 1

# include "ast.h"
# include "scanner.h"

typedef enum
{
  S_GLOBAL,
  S_LOCAL,
  S_PARAM
} Scope;

typedef struct
{
  Scanner *scanner;
  Token token;
  int error_count;
  void *symtable;
  ASTNode *ast;
} Parser;

Parser parser_init(Scanner *scanner);
void parser_parse(Parser *parser);

#endif /* !PARSER_H */
