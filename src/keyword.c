#include <stdlib.h>
#include "keyword.h"

Keyword keywords[] = {
  {"PROCEDURE", T_PROCEDURE},
  {"PROC", T_PROCEDURE},
  {"FUNCTION", T_FUNCTION},
  {"FUNC", T_FUNCTION},
  {"STRUCT", T_STRUCT},
  {"CLASS", T_CLASS},
  {"DECLARE", T_DECLARE},
  {"DCL", T_DECLARE},
  {"AS", T_AS},
  {"PTR", T_PTR},
  {"BEGIN", T_BEGIN},
  {"END", T_END},
  {"WHILE", T_WHILE},
  {"IF", T_IF},

  {NULL, T_ERROR}
};
