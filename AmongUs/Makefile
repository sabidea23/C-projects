CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -utils.h:
LIBS = -lm

SRCS = tasks.c checker.c

OBJS = $(SRCS:.c=.o)

MAIN = amongUs

.PHONY: depend clean

all:    $(MAIN)
	@echo  Your homework has been compiled successfully ^_^

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
