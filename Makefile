FILES = $(shell find . -name '*.cc' -follow -type f -print0 | xargs -0 ls)

# default target
all:
	g++ -g -Wextra -o main $(FILES) -lncurses -lform -lpam -lxcb

# enable extra warning flags -g enable debugging symbols
debug:
	g++ -g -Wextra -o main $(FILES) -lncurses -lform -lpam -lxcb -DDEBUG
	cp main bin/debug/dm_debug

# release build, kinda lighter than debug also all warnings are treated as errors
release:
	g++ -O3 -Wextra -o main $(FILES) -lncurses -lform -lpam -lxcb -DRELEASE
	cp main bin/release/dm

# clean the build
clean:
	rm -rf main
