#ifndef SCANNER_H
# define SCANNER_H

# include <stdio.h>
# include "token.h"

# define COL_START 1
# define LINE_START 1

# define SCAN_BUFFER 512

typedef struct
{
  FILE *fd;
  char const *file;
  
  size_t line;
  size_t col;

  char buffer[SCAN_BUFFER];

  /* for error reporting */
  char linebuffer[SCAN_BUFFER];
 
} Scanner;

Scanner scanner_init(FILE *stream, char const *file);
void scanner_reset(Scanner *scanner);
int scanner_scan(Scanner *scanner, Token *tok);
void scanner_reset(Scanner *scanner);

#endif /* !SCANNER_H */
