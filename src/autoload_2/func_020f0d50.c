/* func_020f0d50 @ 0x020f0d50, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    volatile short x;
    volatile unsigned short count;
    volatile int value;
    volatile int step;
} UnkStruct_020f0d50;

int func_020f0d50(UnkStruct_020f0d50 *s)
{
    unsigned short count;

    count = s->count;
    if (count != 0) {
        count--;
        s->count = count;
        if (s->count != 0) {
            s->value += s->step;
        } else {
            s->value = s->x << 12;
        }
    }
    return (s->value << 4) >> 16;
}
