#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mode.h"
//#include "common.h"

status display_dets(FILE *);
void loading(char *);
status check_id3_tag(FILE *);

#endif
