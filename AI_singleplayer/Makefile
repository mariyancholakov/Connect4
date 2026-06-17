CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRCS = src/main.c src/ai.c src/game_sp.c src/board.c
OBJS = $(SRCS:.c=.o)

TARGET = connect4_singleplayer

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)