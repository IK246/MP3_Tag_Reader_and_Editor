#ifndef COMMON_H
#define COMMON_H

// 
extern char *tags[];
extern char *tag_names[];
char file_tags[50];

status check_id3_tag(FILE *fptr)
{
    int i;

    fread(file_tags, strlen(tags[0]), 1, fptr);
    file_tags[strlen(tags[0])] = '\0';

    if(!strcmp(tags[0], file_tags))
        return e_success;
    else
        return e_failure;
}

void loading()
{
    int t=1;
    char str[20] = "checking";
    int k = strlen(str);

    for(int i=0; i<4; i++)
    {
        printf(Y "\r%s" Re, str);
        fflush(stdout);
        str[k++] = '.';
        str[k] = '\0';
        sleep(1);
    }
}

#endif
