FILES = $(shell ls *.cc)
all:
	g++ -Wall -o main $(FILES) -lncurses -lform

.PHONY: clean

clean:
	rm -rf main
