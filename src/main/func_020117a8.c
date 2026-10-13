/* func_020117a8 @ 0x020117a8, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *addr, unsigned int size);
extern void GX_LoadOBJ(const void *pSrc, unsigned int offset, unsigned int szByte);
extern void GXS_LoadOBJ(const void *pSrc, unsigned int offset, unsigned int szByte);

typedef struct {
    unsigned char pad_00[0x4c];
    char *unk_4C;
} UnkStruct_020117a8;

void func_020117a8(UnkStruct_020117a8 *self)
{
    unsigned int offset;
    unsigned int i;

    DC_FlushRange(self->unk_4C, 0x200);
    offset = 0x3300;
    i = 0;
    goto check;
loop: {
    char *src = self->unk_4C + (i << 8);
    GX_LoadOBJ(src, offset, 0x100);
    GXS_LoadOBJ(src, offset, 0x100);
}
    i++;
    offset += 0x400;
check:
    if (i < 2) {
        goto loop;
    }
}
