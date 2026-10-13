/* func_020116bc @ 0x020116bc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(void *, unsigned int);
extern void GX_LoadOBJ(void *, const void *, unsigned int);
extern void GXS_LoadOBJ(void *, const void *, unsigned int);

struct Unk020116bc {
    unsigned char pad_00[0x4c];
    void *buf;
};

void func_020116bc(struct Unk020116bc *self)
{
    char *src;
    unsigned int i;
    char *dst;

    DC_FlushRange(self->buf, 0x80);
    src = (char *) 0x38c0;
    i = 0;
    goto loop_test;

loop_body:
    dst = (char *) self->buf + (i << 6);
    GX_LoadOBJ(dst, src, 0x40);
    GXS_LoadOBJ(dst, src, 0x40);
    i++;
    src += 0x400;

loop_test:
    if (i < 2) {
        goto loop_body;
    }
}
