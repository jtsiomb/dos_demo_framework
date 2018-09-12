demoobj = main.obj demo.obj screen.obj cfgopt.obj music.obj gfxutil.obj &
3dgfx.obj polyfill.obj polyclip.obj mesh.obj meshload.obj
scrobj = example.obj
sysobj = gfx.obj vbe.obj watdpmi.obj timer.obj keyb.obj mouse.obj sball.obj &
logger.obj tinyfps.obj util.obj dynarr.obj rbtree.obj
obj = $(baseobj) $(demoobj) $(sysobj) $(scrobj)
bin = demo.exe

libs = imago.lib

def = -dM_PI=3.141592653589793
opt = -5 -fp5 -otexan -oh -oi -ei
dbg = -d1

!ifdef __UNIX__
incpath = -Isrc -Isrc/dos -Ilibs/imago/src
libpath = libpath libs/imago libpath
RM = rm -f
!else
incpath = -Isrc -Isrc\dos -Ilibs\imago\src
libpath = libpath libs\imago libpath
RM = del
!endif

AS = nasm
CC = wcc386
CXX = wpp386
ASFLAGS = -fobj
CFLAGS = $(dbg) $(opt) $(def) -zq -bt=dos $(incpath)
CXXFLAGS = $(CFLAGS)
LDFLAGS = option stack=16k option map $(libpath) library { $(libs) }
LD = wlink

$(bin): cflags.occ $(obj) libs/imago/imago.lib
	%write objects.lnk $(obj)
	%write ldflags.lnk $(LDFLAGS)
	$(LD) debug all name $@ system dos4g file { @objects } @ldflags

.c: src;src/dos
.cc: src;src/dos
.asm: src;src/dos

cflags.occ: Makefile
	%write $@ $(CFLAGS)

cxxflags.occ: Makefile
	%write $@ $(CXXFLAGS)

music.obj: music.c
	$(CC) -fo=$@ @cflags.occ -zu $[*

.c.obj: .autodepend
	$(CC) -fo=$@ @cflags.occ $[*

.cc.obj: .autodepend
	$(CXX) -fo=$@ @cxxflags.occ $[*

.asm.obj:
	$(AS) $(ASFLAGS) -o $@ $[*.asm

clean: .symbolic
	$(RM) *.obj
	$(RM) *.occ
	$(RM) *.lnk
	$(RM) $(bin)
