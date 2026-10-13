/* func_0200c41c @ 0x0200c41c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0200c41c {
    char pad_00[0x2d0];
    char unk_2D0;
    char pad_2D1[0x50b];
    int unk_7DC;
    char pad_7E0[0x10];
    int unk_7F0;
    char pad_7F4[8];
    int unk_7FC;
} UnkStruct_0200c41c;

extern int func_02056f94(const void *);
extern int func_02008258(UnkStruct_0200c41c *, int);
extern void func_0200c9a8(UnkStruct_0200c41c *, int, int, int);
extern void func_0200c3b0(UnkStruct_0200c41c *, int, int, int);
extern void func_02095bdc(int);

void func_0200c41c(UnkStruct_0200c41c *p)
{
    if (func_02056f94(&p->unk_2D0)) {
        p->unk_7FC = func_02008258(p, p->unk_7F0);
        if (p->unk_7DC == 5) {
            func_0200c9a8(p, 0, 5, -1);
        } else if (p->unk_7DC == 0x10) {
            func_0200c3b0(p, 0, 5, -1);
        } else {
            func_02095bdc(p->unk_7DC);
        }
    }
}
