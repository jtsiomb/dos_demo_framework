DOS demo framework
==================

About
-----
A loosely-coupled framework for writing retro demos for DOS. It's mostly
targeted towards pentium/pentium2-class computers, with VESA VBE 2.0 capable
graphics cards. Some of the facilities provided by this framework depend on
others, but mostly you can pick and choose what to use, and what to leave out or
rewrite differently.

Here's a non-exhaustive list of things provided by this framework:

 - VESA VBE 2.0 mode setting, page flipping and hardware scrolling.
 - Interrupt-driven timer with selectable tick frequency.
 - Keyboard, mouse, and serial space mouse (6dof) input.
 - Screen abstraction for writing demo parts, and switching between them.
 - GL-like 3D pipeline featuring:
   * Flat, gouraud, texture mapped, and textured-gouraud polygon fillers.
   * Homogeneous frustum polygon/line/point clipping.
   * 3D clipper for user-defined clipping planes.
   * Lighting.
   * Texture-coordinate generation for spherical environment mapping.
 - Mesh loading (OBJ).
 - Image loading (PNG, JPEG, PPM, TGA, RGBE).
 - Perlin noise 1/2/3-d.
 - Miscellaneous utilities: config file parser, resizable arrays, red-black
   trees, fast float to int conversion, framerate counter, logging, RDTSC
   performance measurement.
 - DOS-hosted and cross build with DJGPP and Watcom.
 - SDL 1.2 "emulation" backend for easy hacking and debugging on modern systems.

See example screen in `src/parts/example.c` to see how to write a demo part,
and `scr_init` in `src/screen.c` to see how to register it with the demosystem.

License
-------
Copyright (C) 2018 John Tsiombikas <nuclear@member.fsf.org>

This program is free software. Feel free to use, modify and/or redistribute it
under the terms of the GNU General Public License version 3, or at your option
any later version published by the Free Software Foundation. See COPYING for
details.

Includes code from libpng, jpeglib, and zlib projects. Copyrights for these
parts belong to their respective authors. See the following license files for
details:
 - jpeglib: `libs/imago/jpeglib/README`
 - libpng: `libs/imago/libpng/LICENSE`
 - zlib: `libs/imago/zlib/LICENSE`

TinyFPS (`src/tinyfps.c`) is written by Michael Kargas (Optimus) <optimus6128@yahoo.gr>

Build
-----
From a UNIX shell type `make` to build the SDL version (`GNUmakefile`), type
`make -f Makefile.dj` to cross-compile for DOS with DJGPP, or type `wmake` to
cross-compile for DOS with Watcom.

Under MS-DOS type `make -f Makefile.dj` to build with DJGPP, or type `wmake` to
build with Watcom.

DJGPP or Watcom environment must be set up prior to building with either.
Assembly source files are build with nasm, so make sure you have nasm in your
PATH before starting.
