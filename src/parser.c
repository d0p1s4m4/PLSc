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
static void
function(Parser *parser)
{
  (void)parser;
}
*/

static void
declarations(Parser *parser)
{
  switch (peek(parser)->token)
	{
    case T_IDENT:
	  break;
	case T_PROCEDURE:
	  printf("proc\n");
	  break;
	default:
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
