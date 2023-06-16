/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2023, d0p1
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "term.h"
#include "token.h"

static int
next(Scanner *scanner)
{
  int c;

  c = fgetc(scanner->fd);
  if (c != EOF)
	{
	  if (c == '\t')
		{
		  scanner->linebuffer[scanner->col++] = ' ';
		}
	  else
		{
		  scanner->linebuffer[scanner->col++] = (char)c;
		}
	}
  scanner->linebuffer[scanner->col] = '\0';

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
  scanner->col--;
  scanner->linebuffer[scanner->col] = '\0';
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
comment(Scanner *scanner)
{
  int c;

  c = next(scanner);
  while (c != EOF)
	{
	  if (c == '*')
		{
		  c = next(scanner);
		  if (c == '/')
			{
			  return (c);
			}
		}
	  c = next(scanner);
	}

  if (c == EOF)
	{
	  error_fatal("unexpected EOF in comment");
	}

  return (c);
}

static int
number(Scanner *scanner, Token *tok)
{
  int c;

  c = next(scanner);
  if (c == '0')
	{
	  c = next(scanner);
	  switch (c)
		{
		case 'b':
		  break;

		case 'o':
		  break;

		case 'x':
		  break;

		default:
		  back(scanner, c);
		  break;
		}
	}
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
		  error_fatal("identifier too large");
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

 rescan:
  c = skip(scanner);
  tok->line = scanner->line;
  tok->col = scanner->col;
  tok->linebuffer = scanner->linebuffer;
  tok->file = scanner->file;
  tok->length = 1;

  switch (c)
	{
	case EOF:
	  tok->token = T_EOF;
	  return (0);

	case '/':
	  c = next(scanner);
	  if (c == '*')
		{
		  comment(scanner);
		  goto rescan;
		}
	  else if (c == '=')
		{
		  tok->token = T_LPAREN;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_RPAREN;
		}
	  break;

	case '(':
	  tok->token = T_LPAREN;
	  break;

	case ')':
	  tok->token = T_RPAREN;
	  break;

	case '[':
	  tok->token = T_LSQUARE;
	  break;

	case ']':
	  tok->token = T_RSQUARE;
	  break;

	case ',':
	  tok->token = T_COMMA;
	  break;

	case ':':
	  tok->token = T_COLON;
	  break;

	case ';':
	  tok->token = T_SEMICOLON;
	  break;

	case '+':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_PLUS_EQUAL;
		}
	  else if (c == '+')
		{
		  tok->token = T_PLUS_PLUS;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_PLUS;
		}
	  break;

	case '-':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_MINUS_EQUAL;
		}
	  else if (c == '-')
		{
		  tok->token = T_MINUS_MINUS;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_MINUS;
		}
	  break;

	case '=':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_EQUAL_EQUAL;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_EQUAL;
		}
	  break;

	case '<':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_LESSER_EQUAL;
		}
	  else if (c == '<')
		{
		  tok->token = T_LSHIFT;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_LESSER;
		}
	  break;

	case '>':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_GREATER_EQUAL;
		}
	  else if (c == '>')
		{
		  tok->token = T_RSHIFT;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_GREATER;
		}
	  break;

	case '*':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_ASTERISK_EQUAL;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_ASTERISK;
		}
	  break;

	case '^':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_CARET_EQUAL;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_CARET;
		}
	  break;

	case '%':
	  c = next(scanner);
	  if (c == '=')
		{
		  tok->token = T_MODULO_EQUAL;
		}
	  else
		{
		  back(scanner, c);
		  tok->token = T_MODULO;
		}
	  break;

	case '\'':
	  break;

	case '"':
	  tok->token = T_STRING;
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
		  back(scanner, c);
		  return (number(scanner, tok));
		}
	  else
		{
		  tok->token = T_ERROR;
		  tok->error = E_STRAY;
		  tok->value.intval = c;
		}
	  break;
	}

  return (1);
}