FILES = $(shell find . -name '*.cc' -follow -type f -print0 | xargs -0 ls)
all:
	g++ -Werror -o main $(FILES) -lncurses -lform -lpam

.PHONY: clean

clean:
	rm -rf main