
INC=include


bug.obj: bug.c

.c.obj: 
	echo Compiling $*.c
	com68 -I$(INC) -Oa2s2 -q -g1 -Q $*.c tmpxxx.s
	asm68 -AQkl -I$(INC) -o $*.o tmpxxx.s

