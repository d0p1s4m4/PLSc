#ifndef SYMS_H
# define SYMS_H 1

typedef enum
{
} SymType;

typedef enum
{
  C_GLOBAL,
} SymClass;

typedef struct sym
{
  char *name;
  int size;
  SymType type;
  SymClass class;

  struct sym *next;
} Sym;

#endif /* !SYMS_H */
