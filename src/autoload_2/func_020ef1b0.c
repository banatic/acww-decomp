/* func_020ef1b0 @ 0x020ef1b0, 0x48 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0x36];
    unsigned char count;
} UnkStruct_020ef1b0;

extern void func_020ef1f8(UnkStruct_020ef1b0 *p, int i, int arg);

void func_020ef1b0(UnkStruct_020ef1b0 *p, int arg)
{
    int i = 0;

    if ((int) p->count <= 0) {
        return;
    }

    do {
        func_020ef1f8(p, i, arg);
        i++;
    } while (i < (int) p->count);
}
