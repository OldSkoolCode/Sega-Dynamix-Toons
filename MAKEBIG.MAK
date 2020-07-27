
makefile: objs\\tn_prop.o objs\\tn_chken.o objs\\ball.o objs\\teapot.o \
	objs\\vc.o objs\\scissors.o objs\\gun.o
	touch makefile

objs\\tn_prop.o: tn_chken.c68
	com68 -Iinclude -Oa2s2 -q -g1 -Q tn_prop.c68 objs\\tmpxxx.s
	asm68 -AQkl -Iinclude -o objs\\tn_prop.o objs\\tmpxxx.s

objs\\tn_chken.o: tn_chken.c68
	com68 -Iinclude -Oa2s2 -q -g1 -Q tn_chken.c68 objs\\tmpxxx.s
	asm68 -AQkl -Iinclude -o objs\\tn_chken.o objs\\tmpxxx.s

objs\\ball.o: ball.c68
	com68 -Iinclude -Oa2s2 -q -g1 -Q ball.c68 objs\\tmpxxx.s
	asm68 -AQkl -Iinclude -o objs\\ball.o objs\\tmpxxx.s

objs\\teapot.o: teapot.c68
	com68 -Iinclude -Oa2s2 -q -g1 -Q teapot.c68 objs\\tmpxxx.s
	asm68 -AQkl -Iinclude -o objs\\teapot.o objs\\tmpxxx.s
objs\\vc.o: vc.c68
	com68 -Iinclude -Oa2s2 -q -g1 -Q vc.c68 objs\\tmpxxx.s
	asm68 -AQkl -Iinclude -o objs\\vc.o objs\\tmpxxx.s

objs\\scissors.o: scissors.c68
	com68 -Iinclude -Oa2s2 -q -g1 -Q scissors.c68 objs\\tmpxxx.s
	asm68 -AQkl -Iinclude -o objs\\scissors.o objs\\tmpxxx.s

objs\\gun.o: gun.c68
	com68 -Iinclude -Oa2s2 -q -g1 -Q gun.c68 objs\\tmpxxx.s
	asm68 -AQkl -Iinclude -o objs\\gun.o objs\\tmpxxx.s
