/* The six text archives the game draws random words from for letters (data_020d1a90): "st_music",
 * "st_sports", "st_sweet", "st_drink", "st_object" and "st_food", each with the number of its
 * messages. */
#ifndef CLEAN_MAIN_WORD_ARCHIVES_H
#define CLEAN_MAIN_WORD_ARCHIVES_H

#include "types.h"

#define WORD_ARCHIVES_COUNT 6

typedef struct WordArchive {
    const char *name; /* the archive */
    u8 messages;      /* how many messages it has */
    u8 pad_05[3];
} WordArchive;

int WordArchives_Random(int *message, int archive);

#endif
