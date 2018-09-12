src = $(wildcard src/*.c) \
	  $(wildcard src/3dgfx/*.c) \
	  $(wildcard src/sdl/*.c) \
	  $(wildcard src/parts/*.c)
obj = $(src:.c=.o) $(asmsrc:.asm=.o)
dep = $(obj:.o=.d)
bin = demo

inc = -I/usr/local/include -Isrc -Isrc/sdl -Ilibs/imago/src
warn = -pedantic -Wall -Wno-unused-variable -Wno-unused-function

CFLAGS = $(warn) -g $(inc) `sdl-config --cflags`
LDFLAGS = -Llibs/imago -limago `sdl-config --libs` -lm

$(bin): $(obj) imago
	$(CC) -o $@ $(obj) $(LDFLAGS)

%.o: %.asm
	nasm -f elf -o $@ $<

-include $(dep)

%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: imago
imago:
	$(MAKE) -C libs/imago

.PHONY: cleanlibs
cleanlibs:
	$(MAKE) -C libs/imago clean

.PHONY: clean
clean:
	rm -f $(obj) $(bin)

.PHONY: cleandep
cleandep:
	rm -f $(dep)
