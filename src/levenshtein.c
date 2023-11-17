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
#include <string.h>

#define MIN2(a, b) ((a) < (b) ? (a) : (b))
#define MINIMUM(a, b, c) MIN2(MIN2(a, b), c)

int
levenshtein(char const *s1, char const *s2)
{
  int i;
  int j;
  int len1;
  int len2;
  int *row1;
  int *row2;
  int *tmp;
  int delcost;
  int inscost;
  int subscost;

  len1 = strlen(s1);
  len2 = strlen(s2);

  row1 = (int *)malloc(sizeof(int) * (len2 + 1));
  row2 = (int *)malloc(sizeof(int) * (len2 + 1));

  if (row1 == NULL || row2 == NULL)
	{
	  return (0); /* TODO: error handling */
	}

  for (i = 0; i < len2; i++)
	{
	  row1[i] = i;
	}
  for (i = 0; i < len1; i++)
	{
	  row2[0] = i + 1;
	  for (j = 0; j < len2; j++)
		{
		  delcost = row1[j + 1] + 1;
		  inscost = row2[j] + 1;
		  subscost = row1[j];
		  if (s1[i] != s2[j])
			{
			  subscost += 1;
			}
		  row2[j + 1] = MINIMUM(delcost, inscost, subscost);
		}
	  tmp = row1;
	  row1 = row2;
	  row2 = tmp;
	}

  i = row1[len2];
  free(row1);
  free(row2);

  return (i);
}
