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

static void
declare(Parser *parser)
{
  if (next(parser)->token != T_IDENT)
	{
	  error_fatal("TODO: declare");
	}

  printf("declare(%s)", peek(parser)->value.strval);

  if (next(parser)->token != T_AS)
	{
	  error_fatal("expected AS");
	}

  if (next(parser)->token != T_IDENT)
	{
	  error_fatal("wtf?!");
	}

	printf(" as %s\n", peek(parser)->value.strval);

	while (next(parser)->token != T_SEMICOLON)
	  {}
}

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

		case T_DECLARE:
		  declare(parser);
		  break;

		default:
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
  switch (peek(parser)->token)
	{
	case T_EXTERN:
	  printf("extern\n");
	  break;
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
	  printf("%d\n", peek(parser)->token);
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
