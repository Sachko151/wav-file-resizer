
## Description
The main goal of this program is to resize wav files by either trimming them down to the desired length, or appending silence at the end of the files. The program works with canonical wav files and supports the ability to read metadata tags information, such as artist, year or genre.
## Usage
Available flags:
**-s** *silent flag* - Doesn't show all the logs used for debugging and additional info.
**-o** *overwrite flag* - Replaces original file with resized wav file.
### Build
In order to build wav-file-resizer you have two options.

-   Using `make`:
    
        
        make wav_make
  
-   Using `gcc`:
    
        
       gcc -o wav_resizer main.c src/main_functions.c src/wav_operations.c -I.
      