CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude -I../multiplayer/include

SRCS = src/main.c src/ai.c src/game_sp.c
OBJS = $(SRCS:.c=.o) src/board.o

TARGET = connect4_singleplayer

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/board.o: ../multiplayer/src/board.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
