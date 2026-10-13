/* func_020118a0 @ 0x020118a0, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *, unsigned int);
extern void GX_LoadOBJ(void *, const void *, unsigned int);
extern void GXS_LoadOBJ(void *, const void *, unsigned int);

struct UnkStruct_020118a0 {
    unsigned char pad_00[0x50];
};

void func_020118a0(struct UnkStruct_020118a0 *self, int mode)
{
    char *src;
    char *dst;
    unsigned int i;
    int all, doB, doA;

    DC_FlushRange((char *) self + 0x50, 0x200);

    all = (mode == 0);
    if (all || mode == 1) {
        doA = 1;
    } else {
        doA = 0;
    }
    if (all || mode == 2) {
        doB = 1;
    } else {
        doB = 0;
    }

    src = (char *) 0x1180;
    i = 0;
    goto loop_test;

loop_body:
    dst = (char *) self + 0x50 + (i << 8);
    if (doA) {
        GX_LoadOBJ(dst, src, 0x100);
    }
    if (doB) {
        GXS_LoadOBJ(dst, src, 0x100);
    }
    i++;
    src += 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }
}
