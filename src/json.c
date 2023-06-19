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
#include "error.h"
#include "json.h"

static char *
json_strdup(char const *str)
{
  char *new;

  new = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  if (new == NULL)
	{
	  error_fatal("malloc() failed");
	}
  strcpy(new, str);
  return (new);
}

JSONObj *
json_obj_new(void)
{
  JSONObj *obj;

  obj = (JSONObj *)malloc(sizeof(JSONObj));
  if (obj == NULL)
	{
	  error_fatal("malloc() failed");
	}

  obj->type = JSON_OBJECT;
  obj->next = NULL;
  obj->child = NULL;
  obj->str = NULL;
  obj->num = 0;
  obj->key = NULL;
  return (obj);
}

JSONObj *
json_array_new(void)
{
  JSONObj *obj;

  obj = json_obj_new();
  obj->type = JSON_ARRAY;

  return (obj);
}

JSONObj *
json_string_new(char const *str)
{
  JSONObj *obj;

  obj = json_obj_new();
  obj->type = JSON_STRING;
  obj->str = json_strdup(str);

  return (obj);
}

JSONObj *
json_number_new(int num)
{
  JSONObj *obj;

  obj = json_obj_new();
  obj->type = JSON_NUMBER;
  obj->num = num;

  return (obj);
}

void
json_add_to_obj(JSONObj *obj, char const *key, JSONObj *item)
{
  JSONObj *child;

  if (obj == NULL || item == NULL)
	{
	  error_fatal("null object");
	}

  item->key = key;
  if (obj->child == NULL)
	{
	  obj->child = item;
	  return;
	}

  child = obj->child;
  while (child->next != NULL)
	{
	  child = child->next;
	}
  child->next = item;
}

void
json_add_to_array(JSONObj *array, JSONObj *item)
{
  json_add_to_obj(array, NULL, item);
}

void
json_free(JSONObj *obj)
{
  if (obj == NULL)
	{
	  return;
	}
  json_free(obj->next);
  json_free(obj->child);
  free(obj->str);
  free(obj);
}

void
json_print(JSONObj *obj)
{
  JSONObj *child;

  if (obj == NULL)
	{
	  error_fatal("null object");
	}

  switch (obj->type)
	{
	case JSON_OBJECT:
	  printf("{");
	  child = obj->child;
	  while (child != NULL)
		{
		  printf("\"%s\":", child->key);
		  json_print(child);
		  if (child->next != NULL)
			{
			  printf(",");
			}
		  child = child->next;
		}
	  printf("}");
	  break;

	case JSON_ARRAY:
	  printf("[");
	  child = obj->child;
	  while (child != NULL)
		{
		  json_print(child);
		  if (child->next != NULL)
			{
			  printf(",");
			}
		  child = child->next;
		}
	  printf("]");
	  break;

	case JSON_STRING:
	  printf("\"%s\"", obj->str);
	  break;

	case JSON_NUMBER:
	  printf("%d", obj->num);
	  break;

	default:
	  error_fatal("unknown json type");
	}
}
