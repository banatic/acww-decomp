/* func_02011af8 @ 0x02011af8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void DC_FlushRange(unsigned int, unsigned int);
extern void GX_LoadOBJ(unsigned int, unsigned int, unsigned int);
extern void GXS_LoadOBJ(unsigned int, unsigned int, unsigned int);

struct Func02011A_F8 {
    unsigned char pad_00[0x4c];
    unsigned int unk_4C;
};

void func_02011af8(struct Func02011A_F8 *p, unsigned int a)
{
    DC_FlushRange(p->unk_4C, 0x3000);
    if (a <= 1) {
        GX_LoadOBJ(p->unk_4C, 0x1000, 0x3000);
    }
    if (a == 0 || a == 2) {
        GXS_LoadOBJ(p->unk_4C, 0x1000, 0x3000);
    }
}
