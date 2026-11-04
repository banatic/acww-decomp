/* sound_slots: 2 functions, module autoload_2
 * mwccarm 1.2/base -O4,p
 * func_020ef1b0 @ 0x020ef1b0, 0x48 bytes, ARM
 * func_020ef144 @ 0x020ef144, 0x6c bytes, ARM
 */

typedef struct {
    unsigned char pad_00[0x36];
    unsigned char count;
} UnkStruct_020ef1b0;

extern void func_020ef1f8(UnkStruct_020ef1b0 *p, int i, int arg);
extern int func_020ef8bc(unsigned char *p);

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

void func_020ef144(unsigned char *self, int arg)
{
    int i;
    unsigned char *p;

    i = 0;
    if ((int) self[0x36] > 0) {
        p = self + 8;
        do {
            if (func_020ef8bc(p) != 0) {
                func_020ef1f8((UnkStruct_020ef1b0 *) self, i, arg);
            }
            i = i + 1;
            p = p + 0xc;
        } while (i < (int) self[0x36]);
    }
}
