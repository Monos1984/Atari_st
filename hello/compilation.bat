echo off
set adr_compilateur=..\..\mingw32\bin\
set adr_include=..\..\mingw32\m68k-atari-mint\sys-root\usr\include

set adr_lib=..\..\mingw32\m68k-atari-mint\sys-root\usr\lib\
set adr_code=source/

set nom_programme=bin/hello2.tos 

%adr_compilateur%m68k-atari-mint-gcc-4.6.4 -I%adr_include% -o %nom_programme% %adr_lib%libgem.a %adr_code%*.c

pause