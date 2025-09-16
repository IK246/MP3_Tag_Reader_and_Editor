#ifndef MODE_H
#define MODE_H

typedef enum _mode
{
    e_display,
    e_title,
    e_artist,
    e_album,
    e_year,
    e_genre,
    e_comment,
    e_help,
    e_edit,
    e_invalid
} mode;

typedef enum _status
{
    e_failure,
    e_success
} status;

// color codes
#define R "\x1b[31m"
#define G "\x1b[32m"
#define Y "\x1b[33m"
#define C "\x1b[36m"
#define Re "\x1b[0m"

#endif
