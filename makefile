wav_make: main.c src/main_functions.c src/wav_operations.c
	gcc -o wav_resizer main.c src/main_functions.c src/wav_operations.c -I.
wav_debug: main.c src/main_functions.c src/wav_operations.c
	gcc -o wav_resizer main.c src/main_functions.c src/wav_operations.c -g -I.
clean:
	rm output