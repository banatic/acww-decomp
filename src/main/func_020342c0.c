/* func_020342c0 @ 0x020342c0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x498];
    int minX;
    int maxX;
    int minY;
    int maxY;
} UnkStruct_020342c0;

void *func_020342c0(UnkStruct_020342c0 *self, int x, int y)
{
    if (x >= self->minX && x <= self->maxX && y >= self->minY && y <= self->maxY) {
        return (void *) ((char *) self + 168 * (y - self->minY) + 24 * (x - self->minX));
    }
    return 0;
}
