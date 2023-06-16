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

#ifndef TOKEN_H
# define TOKEN_H 1

# include <stddef.h>
# include <stdint.h>
# include "error.h"

typedef enum {
  T_LPAREN,
  T_RPAREN,
  T_LSQUARE,
  T_RSQUARE,
  T_COLON,
  T_SEMICOLON,
  T_COMMA,
  T_DOT,
  T_MINUS,
  T_PLUS,
  T_LSHIFT,
  T_RSHIFT,
  T_GREATER,
  T_LESSER,
  T_EQUAL,
  T_BANG,
  T_PIPE,
  T_CARET,
  T_AND,
  T_ASTERISK,
  T_MODULO,
  T_SOLIDUS,

  T_ASTERISK_EQUAL,
  T_SOLIDUS_EQUAL,
  T_MODULO_EQUAL,
  T_CARET_EQUAL,
  T_AND_EQUAL,
  T_BANG_EQUAL,
  T_PLUS_EQUAL,
  T_MINUS_EQUAL,
  T_EQUAL_EQUAL,
  T_LESSER_EQUAL,
  T_GREATER_EQUAL,
  T_PLUS_PLUS,
  T_MINUS_MINUS,

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
  T_ERROR,
  T_MAX
} TokenType;

typedef struct token {
  TokenType token;

  /* usefull for error reporting  */
  size_t length;
  size_t line;
  size_t col;
  Error error;

  char const *file;
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