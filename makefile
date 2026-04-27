TARGET = NetSpoofer

CC = gcc
CFLAGS = -Wall -g

DIRS = cli cli/features src
SRCS = $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
OBJS = $(SRCS:.c=.o)

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
