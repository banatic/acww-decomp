/* func_02011b38 @ 0x02011b38, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(unsigned char *p, int n);
extern void GX_LoadOBJPltt(unsigned char *p, int a, int b);
extern void GXS_LoadOBJPltt(unsigned char *p, int a, int b);

typedef struct {
    unsigned char pad_00[0x48];
    unsigned char *data;
} UnkStruct_02011b38;

void func_02011b38(UnkStruct_02011b38 *s, unsigned int mode)
{
    unsigned char *p;
    unsigned char *q;
    DC_FlushRange(s->data, 0x180);
    p = s->data;
    q = p + 0x160;
    if (mode <= 1) {
        GX_LoadOBJPltt(p, 0x80, 0x100);
        GX_LoadOBJPltt(q, 0x1e0, 0x20);
    }
    if (mode == 0 || mode == 2) {
        GXS_LoadOBJPltt(p, 0x80, 0x100);
        GXS_LoadOBJPltt(q, 0x1e0, 0x20);
    }
}
