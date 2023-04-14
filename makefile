wav_make: main.c main_io.c
	gcc -o output main.c main_io.c -I.
clean:
	rm output