# Makefile for Irrlicht Examples
# It's usually sufficient to change just the target name and source file list
# and be sure that CXX is set to a valid compiler
Target = ShoopDaWhoop
Sources = src/*cpp

# general compiler settings
CPPFLAGS = -I../irrlicht-1.8/include -I/usr/X11R6/include -Isrc/include/
#CXXFLAGS = -O3 -ffast-math
CXXFLAGS = -g -Wall

#default target is Linux
all: all_linux

LIBSELECT=64

# target specific settings
all_linux: LDFLAGS = -L/usr/X11R6/lib$(LIBSELECT) -L../irrlicht-1.8/lib/Linux -lIrrlicht -lGL -lXxf86vm -lXext -lX11 -lXcursor
all_linux clean_linux: SYSTEM=Linux
all_win32: LDFLAGS = -L../../lib/Win32-gcc -lIrrlicht -lopengl32 -lm
all_win32 clean_win32: SYSTEM=Win32-gcc
all_win32 clean_win32: SUF=.exe
# name of the binary - only valid for targets which set SYSTEM
DESTPATH = $(Target)

all_linux all_win32:
	$(warning Building...)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(Sources) -o $(DESTPATH) $(LDFLAGS)

clean: clean_linux clean_win32
	$(warning Cleaning...)

clean_linux clean_win32:
	@$(RM) $(DESTPATH)

.PHONY: all all_win32 clean clean_linux clean_win32
