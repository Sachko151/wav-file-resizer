#include "main_io.h"
int main(int argc, char **argv){
    int overwrite_flag = 0;
    int silent_flag = 0;
    check_for_additional_arguments(&overwrite_flag, &silent_flag, argc, argv);
    char filename[32];
    prompt_for_filename_and_fill_in__filename(filename);
    puts(filename);
    check_if_the_filename_is_invalid(filename);
    return 0;
}