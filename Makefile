Project : main.o game.o render.o buttons.o files.o run.o editor.o
	gcc -o Project main.o game.o render.o buttons.o files.o run.o editor.o -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline -laldat -lalld -lalld_s -lalleg -lalleg_s -lallp -lallp_s
main.o : src/main.c
	gcc -c src/main.c -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline
render.o : src/render.c src/render.h
	gcc -c src/render.c -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline
game.o : src/game.c src/game.h
	gcc -c src/game.c -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline
buttons.o : src/buttons.c src/buttons.h
	gcc -c src/buttons.c -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline
files.o : src/files.c src/files.h
	gcc -c src/files.c -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline
run.o : src/run.c src/run.h
	gcc -c src/run.c -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline
editor.o : src/editor.c src/editor.h
	gcc -c src/editor.c -Iallegro-mingw-4.2.2/include -Lallegro-mingw-4.2.2/lib -fgnu89-inline
