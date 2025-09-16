#include "edit.h"

// get array from another file
extern char *tags[];
extern char *tag_names[];

// Function to edit a specific ID3 tag in an MP3 file
status edit_file(FILE *src_fptr, FILE *temp_fptr,  char *data, int index)
{
    unsigned int old_size = 0, new_size = strlen(data)+1;
    char buffer[1024];

    printf(C "Checking For ID3 tag:\n" Re);
    loading("checking");

    // Check if the file has an ID3 tag
    if(check_id3_tag(src_fptr) == e_failure)
    {
        puts(R "\rThe File Does Not Have ID3 Tag" Re);
        return e_failure;
    }
    else
        printf(G "\r%s tag found\n" Re, tags[0]);
    printf("\n");

    rewind(src_fptr); // rewind the source file pointer to the beginning

    // Copy the header
    fread(buffer, 10, 1, src_fptr);
    fwrite(buffer, 10, 1, temp_fptr);

    // loop tom check and edit the specific ID3 tag
    for(int i=1; i<7; i++)
    {
        old_size = 0;
        fread(buffer, 4, 1, src_fptr);
        buffer[4] = '\0';

        if(!strcmp(buffer, tags[index])) // check if the tag matches the one to edit
        {
            printf(C "%s tag found\n" Re, tags[index]);
            puts(C "Coping the tag:" Re);
            loading("coping");

            // Write the tag name
            fwrite(buffer, 4, 1, temp_fptr);
            printf(G "\r%s tag copied\n\n" Re, buffer);

            printf(C "Coping the New %s Size:\n" Re, tag_names[index]);
            loading("coping");

            // Write the new size of the tag
            for(int j=3; j>=0; j--) 
            {
                unsigned char byte = (new_size >> (j * 8)) & 0xFF;
                fwrite(&byte, 1, 1, temp_fptr);
            }
            puts(G "\rSize copied\n" Re);

            // Read the old size of the tag
            for(int j=3; j>=0; j--)
            {
                unsigned char byte;
                fread(&byte, 1, 1, src_fptr);
                old_size |= (byte << (j * 8));
            }

            // Read the tag flags
            fread(buffer, 3, 1, src_fptr);
            fwrite(buffer, 3, 1, temp_fptr);

            printf(C "Coping the New %s:\n" Re, tag_names[index]);
            loading("coping");

            // Write the new data for the tag
            fwrite(data, new_size-1, 1, temp_fptr);
            printf(G "\r%s copied\n\n" Re, tag_names[index]);

            // skip the old data of the tag
            fseek(src_fptr, old_size-1, SEEK_CUR);

            puts(C "Coping Remaining Datas:" Re);
            loading("coping");

            // copy the remaining data from the source file to the temporary file
            copy_remain_data(src_fptr, temp_fptr);
            puts(G "\rRemaining datas copied" Re);

            return e_success;
        }
        else
        {
            // copy the found tag
            fwrite(buffer, 4, 1, temp_fptr);

            // loop to read the size of the tag
            for(int j=3; j>=0; j--)
            {
                unsigned char byte;
                fread(&byte, 1, 1, src_fptr);
                fwrite(&byte, 1, 1, temp_fptr);
                old_size |= (byte << (j * 8));
            }

            // copy the tag size
            fread(buffer, 3, 1, src_fptr);
            fwrite(buffer, 3, 1, temp_fptr);

            // copy the tag data
            fread(buffer, old_size-1, 1, src_fptr);
            fwrite(buffer, old_size-1, 1, temp_fptr);
        }
    }
    return e_failure;
}

// Function to copy the remaining data from the source file to the temporary file
void copy_remain_data(FILE *src_fptr, FILE *temp_fptr)
{
    char ch;
    
    // loop to write the remaining data
    while(fread(&ch, 1, 1, src_fptr) != 0)
        fwrite(&ch, 1, 1, temp_fptr);
}
