#
# Created by gmakemake (Ubuntu Sep  7 2011) on Thu May 10 14:12:56 2012
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

#
# This header.mak file will set up all necessary options for compiling
# and linking C and C++ programs which use OpenGL and/or GLUT on the
# Ubuntu systems.
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
whoami := $(shell whoami)
ifeq (matthew,$(whoami))
# Home computer build profile
INCLUDE =
LIBDIRS =

LDLIBS = -lSOIL -lglut -lGLU -lGL -lXext -lX11 -lm

CFLAGS = -g $(INCLUDE)
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)
else
# CS lab machine build profile
#
# Include file locations
#
GLGLUTINC = /opt/csw/include
SOILINC = /home/fac/wrc/include

INCLUDE = -I$(GLGLUTINC) -I$(SOILINC)

#
# If you are working on a SPARC-based system (e.g., the compute server
# 'queeg'), replace -lSOIL with -lSOIL-sparc in the LDLIBS macro.
#
GLGLUTLIB = /opt/csw/lib
SOILLIB = /home/fac/wrc/lib

GLGLUTLIBDIRS = -L$(GLGLUTLIB)
SOILLIBDIRS = -L$(SOILLIB)

LIBDIRS = $(GLGLUTLIBDIRS) $(SOILLIBDIRS)

LDLIBS = -lSOIL -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm

#
# Compilation and linking flags
#
# If you want to take advantage of GDB's extra debugging features,
# change "-g" in the CFLAGS and LIBFLAGS macro definitions to "-ggdb".
#
CFLAGS = -g $(INCLUDE) -DLABMACHINE
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = -g $(LIBDIRS) $(LDLIBS)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)
endif

########## End of flags from header.mak


CPP_FILES =	camera.cpp hud.cpp project4.cpp scene.cpp stereo.cpp targets.cpp light.cpp texture.cpp
C_FILES =	
PS_FILES =	
S_FILES =	
H_FILES =	camera.h hud.h scene.h stereo.h targets.h vecmath.h light.h texture.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	camera.o hud.o scene.o stereo.o targets.o light.o texture.o

#
# Main targets
#

all:	project4 

project4:	project4.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o project4 project4.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

camera.o:	camera.h
hud.o:	camera.h hud.h scene.h light.h
project4.o:	camera.h hud.h scene.h stereo.h targets.h light.h texture.h
scene.o:	scene.h vecmath.h
stereo.o:	camera.h stereo.h
targets.o:	scene.h targets.h light.h texture.h
light.o:	light.h
texture.o:	texture.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile README
	tar cf - $(SOURCEFILES) Makefile README | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) project4.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf project4 
