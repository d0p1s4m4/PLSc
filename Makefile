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

ifeq ($(OS),Windows_NT)
CFLAGS	+= /TC /Wall /WX /wd5045 /wd4820 /Za /D_CRT_SECURE_NO_WARNINGS
LDFLAGS	+= /SUBSYSTEM:CONSOLE
TARGET	= plsc.exe
else
CFLAGS	+= -Wall -Werror -Wextra -ansi -pedantic
TARGET	= plsc
endif

SRCS	= main.c scanner.c token.c term.c error.c json.c dump.c
OBJS	= $(addprefix src/, $(SRCS:.c=.obj))
ifeq ($(OS),Windows_NT)
DELOBJS	= $(addprefix src\, $(SRCS:.c=.obj))
else
DELOBJS	= $(OBJS)
endif

.PHONY: all
all: $(TARGET)

.PHONY: debug
ifeq ($(OS),Windows_NT)
debug: CFLAGS += /DEBUG /fsanitize=address
debug: LDFLAGS += /DEBUG
else
debug: CFLAGS += -g -fsanitize=address -fsanitize=undefined
debug: LDFLAGS += -g -fsanitize=address -fsanitize=undefined
endif
debug: $(TARGET)

$(TARGET): $(OBJS)
ifeq ($(OS),Windows_NT)
	$(LD) /OUT:$@ $^ $(LDFLAGS)
else
	$(LD) -o $@ $^ $(LDFLAGS)
endif

%.obj: %.c
ifeq ($(OS),Windows_NT)
	$(CC) /Fo:$@ /c $< $(CFLAGS)
else
	$(CC) -o $@ -c $< $(CFLAGS)
endif

.PHONY: test
test: $(TARGET)
	@ $(PYTHON) test/runner.py test

.PHONY: clean
clean:
	$(RM) $(DELOBJS) $(TARGET)
