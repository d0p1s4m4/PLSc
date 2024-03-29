ifeq ($(OS),Windows_NT)
CC		:= cl
LD		:= link
RM		:= cmd /c del /s
RC		:= rc
ISCC	:= iscc
else
CC	?= gcc
LD	:= $(CC)
RM	:= rm -f
endif
TAR		:= tar
PYTHON	:= python3
M4		:= m4

include build-aux/toolchain.mk
include build-aux/version.mk
include build-aux/package.mk

ifdef cc_msvc
CFLAGS	+= /TC /Wall /WX /wd5045 /wd4820 /Za /D_CRT_SECURE_NO_WARNINGS \
			/DVERSION=$(VERSION_STR) /DPACKAGE_BUGREPORT=$(PACKAGE_BUGREPORT_STR)
else

CFLAGS	+= -Wall -Werror -Wextra -DVERSION="$(VERSION_STR)" 
CFLAGS	+= -DPACKAGE_BUGREPORT="$(PACKAGE_BUGREPORT_STR)"
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

ifeq ($(OS),Windows_NT)
DIST_TARGETS	= $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).zip $(PACKAGE)-setup.exe
else
DIST_TARGETS	= $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz
endif

SRCS	= main.c scanner.c token.c term.c error.c json.c dump.c keyword.c \
	parser.c cgen.c cgen-nasm.c cgen-gas.c cgen-athena.c
OBJS	= $(addprefix src/, $(SRCS:.c=.obj))
ifeq ($(OS),Windows_NT)
OBJS	+= win32/res.res
DELOBJS	= $(addprefix src\, $(SRCS:.c=.obj)) win32\res.res
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

%.res: %.rc
	$(RC) /Fo $@ $<

.PHONY: dist
dist: $(DIST_TARGETS)

%.zip: $(TARGET)
	$(TAR) -caf $@ $^

%.tar.gz: $(TARGET)
	$(TAR) -czf $@ $^

$(PACKAGE)-setup.exe: $(TARGET)
	$(ISCC) /Qp win32/setup.iss

.PHONY: test
ifdef cc_msvc
test: LDFLAGS += # /Profile
else
test: CFLAGS += --coverage
test: LDFLAGS += --coverage
endif
test: $(TARGET)
ifdef cc_msvc
#	vsinstr /coverage /verbose $(TARGET)
#	VSPerfCmd /start:coverage /output:test.coverage
#	timeout 3
endif
	@ $(PYTHON) test/runner.py test
ifdef cc_msvc
#	VSPerfCmd /shutdown
endif

.PHONY: check
check: $(TARGET)
	@ $(PYTHON) test/runner.py test

.PHONY: clean
clean:
	$(RM) $(DELOBJS) $(TARGET) $(DIST_TARGETS)
