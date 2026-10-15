/* func_ov003_0220f2f8 @ 0x0220f2f8, 0x4c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2d0];
    unsigned int unk_2D0;
    unsigned int unk_2D4;
    char pad_2D8[0x704 - 0x2d8];
    unsigned int unk_704;
} unk_struct_704;

extern void func_020109a0(unk_struct_704 *p, int b, int c, unsigned short d);
extern void func_02056fcc(unsigned int *p, unsigned int a, int b, int c, unsigned short d);

void func_ov003_0220f2f8(unk_struct_704 *ptr, void *message, int previous)
{
    if (ptr->unk_704 != 0x7a) {
        func_020109a0(ptr, 0x7a, 3, 0);
    }
    {
        unsigned int s;
        unsigned short val;
        s = (ptr->unk_2D4 << 4) >> 16;
        val = (unsigned short) (s - 1);
        func_02056fcc(&ptr->unk_2D0, s, 3, 0x1000, val);
    }
}
