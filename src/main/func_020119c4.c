/* func_020119c4 @ 0x020119c4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *, unsigned int);
extern void GX_LoadOBJ(void *, const void *, unsigned int);
extern void GXS_LoadOBJ(void *, const void *, unsigned int);

struct UnkStruct_020119c4 {
    unsigned char pad_00[0x4c];
    char *unk_4C;
};

void func_020119c4(struct UnkStruct_020119c4 *self, int mode)
{
    char *src;
    int all, doA, doB;
    char *dst;
    unsigned int i;

    DC_FlushRange(self->unk_4C, 0x500);

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

    src = (char *) 0x1000;
    i = 0;
    goto loop_test;

loop_body:
    dst = self->unk_4C + i * 0x280;
    if (doA) {
        GX_LoadOBJ(dst, src, 0x280);
    }
    if (doB) {
        GXS_LoadOBJ(dst, src, 0x280);
    }
    i++;
    src += 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }
}
