wav_make: main.c src/main_functions.c src/wav_operations.c
	gcc -o output main.c src/main_functions.c src/wav_operations.c -I.
gui_make:
	gcc `pkg-config --cflags gtk+-3.0` gui.c src/gui_functions.c -o gui.out `pkg-config --libs gtk+-3.0` -rdynamic -lvlc
clean:
	rm output