/*
 * Name : Karthick I
 * Title : MP3 -> Tag Reader and Editer
 * DAte : 06/09/2025
*/

#include <stdio.h>
#include <string.h>
#include "mode.h"
#include "view.h"
#include "edit.h"

mode operation_type(char *);
status file_validate_and_open(char *, FILE **);
void help_in_modes(void);

// array of tags and their names
char *tags[] = {"ID3", "TIT2", "TPE1", "TALB", "TYER", "TCON", "COMM"};
char *tag_names[] = {"", "Title", "Artist Name", "Album", "Year", "Genre", "Comment"};

int main(int argc, char *argv[])
{
    // Check if the number of arguments is 3 operation is display
    if(argc == 3)
    {
        FILE *fptr;

        // Validate the file name and open the file
        if(file_validate_and_open(argv[2], &fptr) == e_failure)
        {
            puts(R "Invalid Audio File Name" Re);
            return 0;
        }

        // check the operation type
        if(operation_type(argv[1]) == e_display)
        {
            // function to display the details of the mp3 file
            if(display_dets(fptr) == e_failure)
                return 0;
        }
        else
        {
            puts(R "Invalid Mode!!" Re C "\nUsage:\n" Re "To View Details of the mp3 file: ./a.out -v sample.mp3\nTo Edit Details of the mp3 file: ./a.out -e -[t/a/A/y/c/g/h] sample.mp3 *your_data*\n");
            help_in_modes();
            return 0;
        }
    }
    else if((argc == 5) && (operation_type(argv[1]) == e_edit)) // Check if the number of arguments is 5 and the operation is edit
    {
        FILE *fptr1, *fptr2 = fopen("temp.mp3", "w");
        if(fptr2 == NULL)
        {
            puts("Temp File Not Opened");
            return 0;
        }
        // check the operation type
        if((operation_type(argv[2])) != e_invalid)
        {
            // Validate the file name and open the file
            if(file_validate_and_open(argv[3], &fptr1) == e_failure)
            {
                puts(R "Invalid Audio File Name" Re);
                return 0;
            }
            // function to edit the given tag in the mp3 file
            if(edit_file(fptr1, fptr2, argv[4], operation_type(argv[2])) == e_success)
            {
                remove(argv[3]);
                rename("temp.mp3", argv[3]);
            }
        }
    }
    // check if the number of arguments is 2 and the operation is help
    else if((argc == 2) && (operation_type(argv[1]) == e_help))
        help_in_modes();
    else
    {
        puts(R "Command Line Argument Should be 3!!\n" Re C "Usage:\n" Re "To View Details of the mp3 file: ./a.out -v sample.mp3\nTo Edit Details of the mp3 file: ./a.out -e -[t/a/A/y/c/g/h] sample.mp3 *your_data*\n");
        help_in_modes();
        return 0;
    }
    return 0;
}

mode operation_type(char *oper)
{
    // check the opertion type and return the enum value
    if(!strcmp(oper, "-v"))
        return e_display;
    else if(!strcmp(oper, "-t"))
        return e_title;
    else if(!strcmp(oper, "-a"))
        return e_artist;
    else if(!strcmp(oper, "-A"))
        return e_album;
    else if(!strcmp(oper, "-y"))
        return e_year;
    else if(!strcmp(oper, "-g"))
        return e_genre;
    else if(!strcmp(oper, "-c"))
        return e_comment;
    else if(!strcmp(oper, "-h"))
        return e_help;
    else if(!strcmp(oper, "-e"))
        return e_edit;
    else
        return e_invalid;
}

// Function to validate the file name and open the file
status file_validate_and_open(char *fname, FILE **fptr)
{
    char *ptr;
    if((ptr = strstr(fname, ".mp3")) != NULL)
    {
        if(!strcmp(ptr, ".mp3"))
        {
            if((*fptr = fopen(fname, "r")) == NULL)
            {
                printf(R "%s File Not Opened\n" Re, fname);
                return e_failure;
            }
            printf(G "File Opened Successfully\n" Re);
            return e_success;
        }
        else
        {
            printf(R "Extension Is Mispaced %s\n" Re, fname);
            return e_failure;
        }
    }
    else
    {
        printf(R "File Name Should Contain .mp3 Extension\n" Re);
        return e_failure;
    }
}

void help_in_modes(void)
{
    puts("Usage message:\n");
    puts("-t\tTo modify a Title");
    puts("-a\tTo modify a Artist Name");
    puts("-A\tTo modify a Album Name");
    puts("-y\tTo modify a Year");
    puts("-c\tTo modify a Comment");
    puts("-g\tTo modify a Genre");
    puts("-h\tTo display help info");
    puts("-v\tTo view mp3 file all details");
    puts("To View Details of the mp3 file: ./a.out -v sample.mp3\nTo Edit Details of the mp3 file: ./a.out -e -[t/a/A/y/c/g/h] sample.mp3 *your_data*\n");
}