FILES = $(shell ls *.cc)
all:
	g++ -Wall -o main $(FILES) -lncurses -lform -lpam

.PHONY: clean

clean:
	rm -rf main
