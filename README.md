ShootSpacer
===========


To compile as Static LIB link against:

[ShootSpacer_Static_Library]  ( * optional - only if compiling as static library for running tests)
kernel32
user32
gdi32
winspool
comdlg32
advapi32
shell32
ole32
oleaut32
uuid
Irrlicht

Directories with libraries (for Eclipse):

"${workspace_loc:/ShootSpacer_Static_Library/Debug}"
"C:\MinGW\lib"
"${workspace_loc:${workspace_loc}/}"
"${workspace_loc:/Irrlicht/lib/Win32-gcc-dbg}"

Explanation: workspace_loc - location of workspace directory (one level above source)
Mingw- mingw libraries (or else if using different compiler)

precompiled header:
 D:\Moje\programowanie\eclipse_cpp\ShootSpacer\source>g++ -D_IRR_STATIC_LIB_ -I"D:\Moje\programowanie\eclipse_cpp\ShootSpacer\ext\irrlicht-1.8\include" -I"D:\Moje\programowanie\eclipse_cpp\ShootSpacer\source" -I"D:\Moje\programowanie\eclipse_cpp\ShootSpacer\source\shootspacer" -I"D:\Moje\programowanie\eclipse_cpp\ShootSpacer\source\helpers" -I"D:\Moje\programowanie\eclipse_cpp\ShootSpacer\source\patterns" -I"D:\Moje\programowanie\eclipse_cpp\ShootSpacer\ext\boost" -O1 -g3 -Wall -c -fmessage-length=0 -c stdafx.h -o stdafx.h.gch