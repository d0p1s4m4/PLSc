ifeq ($(OS),Windows_NT)
CC	:= cl
LD	:= link
RM	:= cmd /c del /s
else
CC	?= gcc
LD	:= $(CC)
RM	:= rm -f
endif

ifeq ($(OS),Windows_NT)
CFLAGS	+= /TC /Wall /WX /wd5045 /Za
LDFLAGS	+= /SUBSYSTEM:CONSOLE
TARGET	= plsc.exe
else
CFLAGS	+= -Wall -Werror -Wextra -ansi 
TARGET	= plsc
endif

SRCS	= main.c
OBJS	= $(addprefix src/, $(SRCS:.c=.obj))
ifeq ($(OS),Windows_NT)
DELOBJS	= $(addprefix src\, $(SRCS:.c=.obj))
else
DELOBJS	= $(OBJS)
endif

.PHONY: all
all: $(TARGET)

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

.PHONY: clean
clean:
	$(RM) $(DELOBJS) $(TARGET)
