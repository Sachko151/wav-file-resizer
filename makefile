wav_make: main.c main_io.c wav_operations.c
	gcc -o output main.c main_io.c wav_operations.c -I.
clean:
	rm output