CFLAGS = -Wall -std=c99 -O2
SRC_FILES := src/main.c src/console.c src/prompts.c src/text_graphics.c src/trading.c src/weather.c
INCLUDE_FLAGS = -Iinclude

dev: $(SRC_FILES)
	$(CC) $(CFLAGS) -Werror -Wextra -Wpedantic -g $(INCLUDE_FLAGS) $(SRC_FILES) -o a.out

macos: $(SRC_FILES)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(SRC_FILES) -o a.out

windows: $(SRC_FILES)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(SRC_FILES) -o a.exe
