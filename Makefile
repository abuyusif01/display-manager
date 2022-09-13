FILES = $(shell find . -name '*.cc' -follow -type f -print0 | xargs -0 ls)

# default target
all:
	g++ -g -Werror -o main $(FILES) -lncurses -lform -lpam

# enable extra warning flags -g enable debugging symbols 
debug:
	g++ -g -Wextra -o main $(FILES) -lncurses -lform -lpam -DDEBUG

# release build, kinda lighter than debug also all warnings are treated as errors
release:
	g++ -O3 -Werror -o main $(FILES) -lncurses -lform -lpam -DRELEASE

# clean the build
clean:
	rm -rf main
