#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "term.h"

static void
error(Scanner *scanner, int c)
{
  fprintf(stderr, "%s:%zu:%zu: ", scanner->file, scanner->line, scanner->col);
  term_color_red(stderr);
  fprintf(stderr, "error:");
  term_color_reset(stderr);
  fprintf(stderr, " stray '%c' in program\n", (char)c);
  fprintf(stderr, " %5zu | %s\n", scanner->line, scanner->linebuffer);
  fprintf(stderr, "       | ");
  term_color_red(stderr);
  fprintf(stderr, "%*c\n", (int)scanner->col, '^');
  term_color_reset(stderr);

  exit(EXIT_FAILURE);
}

static int
next(Scanner *scanner)
{
  int c;

  c = fgetc(scanner->fd);
  if (c != EOF)
	{
	  scanner->linebuffer[scanner->col++] = (char)c;
	  scanner->linebuffer[scanner->col] = '\0';
	}

  if (c == '\n')
	{
	  scanner->line++;
	  scanner->col = 0;
	}
  return (c);
}

static int
back(Scanner *scanner, int c)
{
  if (c == '\n')
	{
	  scanner->line--;
	}

  ungetc(c, scanner->fd);
  return (c);
}

static int
skip(Scanner *scanner)
{
  int c;

  c = next(scanner);
  while (isspace(c))
	{
	  c = next(scanner);
	}
  return (c);
}

static int
number(Scanner *scanner, Token *tok)
{
  (void)scanner;
  (void)tok;

  return (1);
}

static int
ident(Scanner *scanner, Token *tok)
{
  size_t idx;
  int c;

  idx = 0;
  c = next(scanner);
  while (isalpha(c) || isdigit(c) || '_' == c)
	{
	  if (idx >= SCAN_BUFFER - 1)
		{
		  exit(EXIT_FAILURE); /* TODO: error */
		}
	  else
		{
		  scanner->buffer[idx++] = (char)c;
		}
	  c = next(scanner);
	}

  back(scanner, c);
  scanner->buffer[idx] = '\0';

  tok->length = idx;
  tok->value.strval = scanner->buffer;

  return (1);
}

void
scanner_reset(Scanner *scanner)
{
  scanner->line = LINE_START;
  scanner->col = 0;

  fseek(scanner->fd, 0, SEEK_SET);
}

Scanner
scanner_init(FILE *stream, char const *file)
{
  Scanner scanner;

  scanner.fd = stream;
  scanner.file = file;

  scanner_reset(&scanner);

  return (scanner);
}

int
scanner_scan(Scanner *scanner, Token *tok)
{
  int c;

  c = skip(scanner);
  tok->line = scanner->line;
  tok->col = scanner->col;
  tok->length = 1;

  switch (c)
	{
	case EOF:
	  tok->token = T_EOF;
	  return (0);

	case '(':
	  tok->token = T_LPAREN;
	  break;

	case ')':
	  tok->token = T_RPAREN;
	  break;

	case ':':
	  tok->token = T_COLON;
	  break;

	case ';':
	  tok->token = T_SEMICOLON;
	  break;

	default:
	  if (isalpha(c) || c == '_')
		{
		  back(scanner, c);
		  tok->token = T_IDENT;
		  return (ident(scanner, tok));
		}
	  else if (isdigit(c))
		{
		  return (number(scanner, tok));
		}
	  else
		{
		  error(scanner, c);
		}
	  break;
	}

  return (1);
}
