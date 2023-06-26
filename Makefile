ifeq ($(OS),Windows_NT)
CC	:= cl
LD	:= link
RM	:= cmd /c del /s
else
CC	?= gcc
LD	:= $(CC)
RM	:= rm -f
endif
PYTHON := python3

include build-aux/toolchain.mk
include build-aux/version.mk

ifdef cc_msvc
CFLAGS	+= /TC /Wall /WX /wd5045 /wd4820 /Za /D_CRT_SECURE_NO_WARNINGS \
			/DVERSION=$(VERSION_STR)
else

CFLAGS	+= -Wall -Werror -Wextra -DVERSION="$(VERSION_STR)"
ifdef cc_clang_gcc
CFLAGS	+= -ansi -pedantic
endif
endif

ifdef ld_msvc
LDFLAGS	+= /SUBSYSTEM:CONSOLE
endif


ifeq ($(OS),Windows_NT)
TARGET	= plsc.exe
else
TARGET	= plsc
endif

SRCS	= main.c scanner.c token.c term.c error.c json.c dump.c keyword.c \
	parser.c cgen.c cgen-nasm.c cgen-gas.c cgen-athena.c
OBJS	= $(addprefix src/, $(SRCS:.c=.obj))
ifeq ($(OS),Windows_NT)
DELOBJS	= $(addprefix src\, $(SRCS:.c=.obj))
else
DELOBJS	= $(OBJS)
endif

.PHONY: all
all: $(TARGET)

.PHONY: debug
ifdef cc_msvc
debug: CFLAGS += /DEBUG /fsanitize=address
debug: LDFLAGS += /DEBUG
else
debug: CFLAGS += -g -fsanitize=address -fsanitize=undefined
debug: LDFLAGS += -g -fsanitize=address -fsanitize=undefined
endif
debug: $(TARGET)

$(TARGET): $(OBJS)
ifdef ld_msvc
	$(LD) /OUT:$@ $^ $(LDFLAGS)
else
	$(LD) -o $@ $^ $(LDFLAGS)
endif

%.obj: %.c
ifdef cc_msvc
	$(CC) /Fo:$@ /c $< $(CFLAGS)
else
	$(CC) -o $@ -c $< $(CFLAGS)
endif

.PHONY: test
test: CFLAGS += --coverage
test: LDFLAGS += --coverage
test: $(TARGET)
	@ $(PYTHON) test/runner.py test

.PHONY: check
check: $(TARGET)
	@ $(PYTHON) test/runner.py test

.PHONY: clean
clean:
	$(RM) $(DELOBJS) $(TARGET)
