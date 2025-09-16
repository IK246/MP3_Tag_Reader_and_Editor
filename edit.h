#ifndef EDIT_H
#define EDIT_H

#include <stdio.h>
#include <string.h>
#include "mode.h"

status edit_file(FILE *, FILE *, char *, int);
void copy_remain_data(FILE *, FILE *);
status check_id3_tag(FILE *);
void loading(char *);

#endif
