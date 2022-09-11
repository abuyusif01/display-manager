FILES = $(shell find . -name '*.cc' -follow -type f -print0 | xargs -0 ls)
all:
	.PHONY: clean
	g++ -Werror -o main $(FILES) -lncurses -lform -lpam
	
clean:
	rm -rf main