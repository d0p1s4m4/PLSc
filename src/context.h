#ifndef CONTEXT_H
# define CONTEXT_H 1

# include "syms.h"

typedef struct context {
  struct context *parent;
  Sym *syms;
} Context;

extern Context context_global;

Context *context_create(Context *parent);
void context_destroy(Context *context);

#endif /* !CONTEXT_H */
