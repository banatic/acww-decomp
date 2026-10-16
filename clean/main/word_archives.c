/* The word archives (word_archives.h). */
#include "word_archives.h"

#include "clean.h"

static_assert(sizeof(WordArchive) == 8, "WordArchive is 8 bytes");

extern u32 func_020644cc(int range); /* a random number below `range` */

extern const WordArchive data_020d1a90[WORD_ARCHIVES_COUNT];

/* func_0209c54c: a message of archive `archive` drawn at random into `*message`; the archive's
 * name (a pointer, as an int). */
int WordArchives_Random(int *message, int archive)
{
    *message = (int) func_020644cc(data_020d1a90[archive].messages);
    return (int) (uintptr_t) data_020d1a90[archive].name;
}
CLEAN_AS(func_0209c54c, WordArchives_Random)
