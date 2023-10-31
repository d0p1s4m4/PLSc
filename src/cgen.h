#ifndef CGEN_H
# define CGEN_H 1

typedef struct
{
  const char *name;
} Backend;

# define CGEN_BACKEND(_name) \
  Backend cgen_ ## _name = { \
	#_name \
  }

void cgen_init(void);

extern Backend cgen_nasm;
extern Backend cgen_gas;
extern Backend cgen_c;

#endif /* !CGEN_H */
