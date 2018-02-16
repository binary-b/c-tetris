PROG_NAME = calculator

CC = gcc
CFLAGS = -Wall -Wfatal-errors -ggdb -Iinclude
CLIB_ALLEGRO != pkg-config --cflags --libs \
	allegro-5 \
	allegro_image-5 \
	allegro_font-5 \
	allegro_ttf-5 \
	allegro_primitives-5
SDT = -D_GNU_SOURCE

#SRC_DIRS != find src -type d
SRC  != cd src && find -regex '.*\.c'
OBJS := $(SRC:.c=.o)
HEADERS != cd src && find -regex '.*\.h'

vpath %.c ./src
vpath %.h ./src
vpath %.o ./obj

$(PROG_NAME) : $(OBJS)
	cd obj && $(CC) $(CFLAGS) $(STD) $(CLIB_ALLEGRO) -o ../$(PROG_NAME) $(OBJS)

clean:
	rm -r --force obj

clobber: clean
	rm $(PROG_NAME) --force

%.o : %.c $(HEADERS)
	@mkdir --parents obj/$(@D)
	$(CC) -c $(CFLAGS) $(STD) $(CLIB_ALLEGRO) -o obj/$@ $<

stats: $(SRC) $(HEADERS)
	@cd src
	@echo lines words chars
	@wc $^
