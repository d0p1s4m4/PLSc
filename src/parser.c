#include "parser.h"
#include "token.h"

static Token *
next(Parser *parser)
{
  while (scanner_scan(parser->scanner, &parser->token) != 0)
	{
	  if (parser->error_count > 16)
		{
		  error_fatal("too many error, aborting...");
		}

	  if (parser->token.token == T_ERROR)
		{
		  error_tok(&parser->token);
          parser->error_count++;
		}
	  else
		{
		  return (&parser->token);
		}
	}

  return (&parser->token);
}

static Token *
peek(Parser *parser)
{
  return (&parser->token);
}

Parser
parser_init(Scanner *scanner)
{
  Parser parser;

  parser.scanner = scanner;
  parser.error_count = 0;
  parser.ast = NULL;
  return (parser);
}

/*
 * unit
 *  : external_declaration
 *  | unit external_declaration
 *  ;
 *
 * external_declaration
 *  : function_definition
 *  | declaration
 *  ;
 *
 * function_definition
 *  : T_PROCEDURE declarator ';' compound_statement
 *  TODO: | T_FUNCTION T_IDENT ';' compound_statement
 *  ;
 *
 * declarator
 *  : T_IDENTIFIER
 *  | T_IDENTIFIER '(' ')'
 *  | T_IDENTIFIER '(' parameter_list ')'
 *
 *
 */

static void
type(Parser *parser)
{
  if (next(parser)->token != T_IDENT)
	{
	  error_fatal("expected type identifier");
	}

  printf(" %s ", peek(parser)->value.strval);

  if (next(parser)->token == T_PTR)
	{
	  printf(" ptr ");
	  next(parser);
	}
  else if (peek(parser)->token == T_LPAREN)
	{
	  if (next(parser)->token == T_NUMBER)
		{
		  printf(" ARRAY[%s] ", peek(parser)->value.strval);
		}
	  else
		{
		  error_fatal("expected number");
		}

	  if (next(parser)->token == T_RPAREN)
		{
		  next(parser);
		}
	  else
		{
		  error_fatal("expected )");
		}
	}
}

static void
declare(Parser *parser)
{
  if (next(parser)->token != T_IDENT)
	{
	  error_fatal("expected identifier");
	}

  printf("declare(%s)", peek(parser)->value.strval);

  if (next(parser)->token != T_AS)
	{
	  error_fatal("expected AS");
	}

  type(parser);

  if (peek(parser)->token != T_SEMICOLON)
	{
	  error_fatal("expected ';'");
	}

  printf("\n");
}

#if 0
static void
if_stmt(Parser *parser)
{
  (void)parser;
}

static void
while_stmt(Parser *parser)
{
  (void)parser;
}

static void
for_stmt(Parser *parser)
{
  (void)parser;
}

static void
return_stmt(Parser *parser)
{
  (void)parser;
}
#endif

static void
block(Parser *parser)
{
  printf("BLOCK_BEGIN(\n");

  while (next(parser)->token != T_END)
	{
	  switch (peek(parser)->token)
		{
		case T_EOF:
		  error_fatal("unexpected eof");
		  break;

		case T_BEGIN:
		  block(parser);
		  break;

		case T_WHILE:
		  printf("while\n");
		  block(parser);
		  break;

		case T_IF:
		  printf("IF stmt\n");
		  while (next(parser)->token != T_SEMICOLON) {}
		  break;

		case T_LSQUARE:
		  printf("[method call]\n");
		  while (next(parser)->token != T_SEMICOLON){}
		  break;

		case T_DECLARE:
		  declare(parser);
		  break;

		case T_IDENT:
		  printf("identifier TODO\n");
		  break;

		default:
		  printf("????\n");
		  break;
		}
	}
  printf(")BlockEnd\n");
}

static void
function(Parser *parser, int is_proc)
{
  if (next(parser)->token == T_IDENT)
	{
	  if (is_proc)
		{
		  printf("proc(%s)\n", peek(parser)->value.strval);
		}
	  else
		{
		  printf("func(%s)\n", peek(parser)->value.strval);
		}
	}

  while (next(parser)->token != T_SEMICOLON)
	{}
  block(parser);
}

static void
declarations(Parser *parser)
{
  /*int is_extern;

	is_extern = 0;*/
  if (peek(parser)->token == T_EXTERN)
	{
	  /*  is_extern = 1;*/
	  printf("extern ");
	  next(parser);
	}

  switch (peek(parser)->token)
	{
	case T_DECLARE:
	  declare(parser);
	  break;
	case T_PROCEDURE:
	  function(parser, 1);
	  break;
	case T_FUNCTION:
	  function(parser, 0);
	  break;
	default:
	  error_fatal("not a decl");
	  break;
	}
}

void
parser_parse(Parser *parser)
{
  while (next(parser)->token != T_EOF)
	{
	  if (peek(parser)->token != T_SEMICOLON)
		{
		  declarations(parser);
		}
	}
}
