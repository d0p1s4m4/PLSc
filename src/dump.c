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
#include <errno.h>
#include "scanner.h"
#include "json.h"

static JSONObj *
token_position_to_json(Token *tok)
{
  JSONObj *obj;

  obj = json_obj_new();
  json_add_to_obj(obj, "column", json_number_new(tok->col));
  json_add_to_obj(obj, "line", json_number_new(tok->line));
  json_add_to_obj(obj, "length", json_number_new(tok->length));

  return (obj);
}

static JSONObj *
error_token_to_json(Token *tok)
{
  JSONObj *obj;

  obj = json_obj_new();
  json_add_to_obj(obj, "position", token_position_to_json(tok));

  return (obj);
}

static JSONObj *
token_to_json(Token *tok)
{
  JSONObj *obj;

  obj = json_obj_new();
  json_add_to_obj(obj, "type", json_string_new(token_to_str(tok->token)));
  if (tok->token == T_IDENT)
	{
	  json_add_to_obj(obj, "value", json_string_new(tok->value.strval));
	}
  json_add_to_obj(obj, "position", token_position_to_json(tok));

  return (obj);
}

void
dump_tokens(char const *file)
{
  FILE *fp;
  Scanner scanner;
  Token tok;
  JSONObj *obj;
  JSONObj *tok_array;
  JSONObj *err_array;

  fp = fopen(file, "r");
  if (fp == NULL)
	{
	  error_fatal("%s: %s", file, strerror(errno));
	}

  scanner = scanner_init(fp, file);

  obj = json_obj_new();
  tok_array = json_array_new();
  err_array = json_array_new();

  while (scanner_scan(&scanner, &tok) != 0)
	{
	  if (tok.token == T_ERROR)
		{
		  json_add_to_array(err_array, error_token_to_json(&tok));
		}
	  else
		{
		  json_add_to_array(tok_array, token_to_json(&tok));
		}
	}

  json_add_to_obj(obj, "file", json_string_new(file));
  json_add_to_obj(obj, "tokens", tok_array);
  json_add_to_obj(obj, "errors", err_array);
  json_print(obj);
  json_free(obj);
}
