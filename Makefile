# Wedit Makefile for project nexsus
CFLAGS=-I/usr/include -I/usr/include/SDL `sdl-config --cflags`
CC=gcc
OBJS=\
	nexsusmain.o \
	nexsussystem.o \
	nexsususer.o \
	nexsusutil.o \
	nexsusobj.o \
	nexsuscore.o \
	enemy.o \
	enemy2.o \
	wall.o \
	myship.o \
	missile_control.o \
	missile.o

LIBS=`sdl-config --libs` -lSDL_image -lSDL_mixer

nexsus:	$(OBJS) Makefile
	$(CC)  -o nexsus $(OBJS) $(LIBS)

# Build nexsusmain.c
NEXSUSMAIN_C=\

nexsusmain.o: $(NEXSUSMAIN_C) src/nexsusmain.c src/nexsusdef.h src/nexsusdev.h
	$(CC) -c $(CFLAGS) src/nexsusmain.c

# Build nexsussystem.c
NEXSUSSYSTEM_C=\

nexsussystem.o: $(NEXSUSSYSTEM_C) src/nexsussystem.c src/nexsussystem.h src/nexsusdef.h src/nexsusdev.h
	$(CC) -c $(CFLAGS) src/nexsussystem.c

# Build nexsususer.c
NEXSUSUSER_C=\

nexsususer.o: $(NEXSUSUSER_C) src/nexsususer.c src/nexsususer.h src/nexsusdef.h src/nexsusdev.h
	$(CC) -c $(CFLAGS) src/nexsususer.c

# Build nexsusutil.c
NEXSUSUTIL_C=\

nexsusutil.o: $(NEXSUSUTIL_C) src/nexsusutil.c src/nexsusutil.h src/nexsusdef.h src/nexsusdev.h
	$(CC) -c $(CFLAGS) src/nexsusutil.c

# Build nexsuscore.c
NEXSUSCORE_C=\

nexsuscore.o: $(NEXSUSCORE_C) src/nexsuscore.c src/nexsuscore.h src/nexsusdef.h src/nexsusdev.h
	$(CC) -c $(CFLAGS) src/nexsuscore.c

# Build nexsusobj.c
NEXSUSOBJ_C=\

nexsusobj.o: $(NEXSUSOBJ_C) src/nexsusobj.c src/nexsusobj.h src/nexsusdef.h src/nexsusdev.h
	$(CC) -c $(CFLAGS) src/nexsusobj.c

# Build enemy.c
ENEMY_C=\

enemy.o: $(ENEMY_C) src/enemy.c src/nexsus.h
	$(CC) -c $(CFLAGS) src/enemy.c

# Build enemy2.c
ENEMY2_C=\

enemy2.o: $(ENEMY2_C) src/enemy2.c src/nexsus.h
	$(CC) -c $(CFLAGS) src/enemy2.c

# Build wall.c
WALL_C=\

wall.o: $(WALL_C) src/wall.c src/nexsus.h
	$(CC) -c $(CFLAGS) src/wall.c

# Build myship.c
MYSHIP_C=\

myship.o: $(MYSHIP_C) src/myship.c src/nexsus.h
	$(CC) -c $(CFLAGS) src/myship.c

# Build missile.c
MISSILE_C=\

missile.o: $(MISSILE_C) src/missile.c src/nexsus.h
	$(CC) -c $(CFLAGS) src/missile.c

# Build missile_control.c
MISSILE_CONTROL_C=\

missile_control.o: $(MISSILE_CONTROL_C) src/missile_control.c src/nexsus.h
	$(CC) -c $(CFLAGS) src/missile_control.c

