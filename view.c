#include "view.h"

extern char *tags[];
extern char *tag_names[];
char file_tags[50];

// Function to display the details of an MP3 file
status display_dets(FILE *fptr)
{
    int size;

    printf(C "Checking For ID3 tag:\n" Re);
    loading("checking");

    // Check if the file has an ID3 tag
    if(check_id3_tag(fptr) == e_failure)
    {
        puts(R "\rThe File Does Not Have ID3 Tag" Re);
        return e_failure;
    }
    else
        printf(G "\r%s tag found\n" Re, tags[0]);
    printf("\n");

    fseek(fptr, 7, SEEK_CUR); // Skip the ID3 header

    for(int i=1; i<=6; i++)
    {
        size = 0;
        printf(C "Checking for %s tag:\n" Re, tags[i]);
        loading("checking");

        // Read the tag name
        fread(file_tags, 4, 1, fptr);
        file_tags[4] = '\0';

        int k;

        // Check if the tag matches
        for(k=1; k<7; k++)
        {
            // Compare the tag name with the array of tags
            if(!strcmp(file_tags, tags[k]))
            {
                printf(G "\r%s tag found\n" Re, tags[i]);
                for (int j=3; j>=0; j--) 
                {
                    unsigned char byte;
                    fread(&byte, 1, 1, fptr);
                    size |= (byte << (j * 8));
                }

                fseek(fptr, 3, SEEK_CUR); // Skip the tag flags

                // print the tag data
                printf("%s: ", tag_names[k]);
                for(int j=0; j<size-1; j++)
                    printf("%c", fgetc(fptr));
                printf("\n");
                break;
            }
        }
        if(k == 7)
        {
            printf(R "\rTag not found\n" Re);
            return e_failure;
        }
    }
}

// function to check if the file has an ID3 tag
status check_id3_tag(FILE *fptr)
{
    int i;

    // read the first 3 bytes to check for the ID3 tag
    fread(file_tags, strlen(tags[0]), 1, fptr);
    file_tags[strlen(tags[0])] = '\0';

    // Compare the read tag with the expected ID3 tag
    if(!strcmp(tags[0], file_tags))
        return e_success;
    else
        return e_failure;
}

// Function to display a loading message
void loading(char str[])
{
    int t=1;
    char str1[20];
    strcpy(str1, str);
    int k = strlen(str);

    // Print the loading message
    for(int i=0; i<4; i++)
    {
        printf(Y "\r%s" Re, str1);
        fflush(stdout);
        str1[k++] = '.';
        str1[k] = '\0';
        usleep(300000);
    }
}
