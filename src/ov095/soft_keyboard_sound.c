/* soft_keyboard_sound: 6 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * func_ov095_022999f4 @ 0x022999f4, 0xc bytes, Thumb
 * func_ov095_022999e8 @ 0x022999e8, 0xc bytes, Thumb
 * func_ov095_022999c0 @ 0x022999c0, 0x28 bytes, Thumb
 * func_ov095_022999b0 @ 0x022999b0, 0x10 bytes, Thumb
 * func_ov095_022999a8 @ 0x022999a8, 0x8 bytes, Thumb
 * func_ov095_022999a0 @ 0x022999a0, 0x8 bytes, Thumb
 */

struct UnkStruct_022999b0 {
    unsigned char pad_00[20];
    unsigned short unk_14;
};

extern void func_0200467c(int);
extern int func_0200457c(int a);

int func_ov095_022999b0(struct UnkStruct_022999b0 *p, unsigned int mask);
void func_ov095_022999a8(unsigned short *p0, int p1);

void func_ov095_022999f4(void *receiver)
{
    func_0200467c(22);
}

void func_ov095_022999e8(void *receiver)
{
    func_0200467c(23);
}

void func_ov095_022999c0(int a, int b)
{
    if (func_ov095_022999b0((struct UnkStruct_022999b0 *) a, 0x200) == 0) {
        func_ov095_022999a8((unsigned short *) a, 0x200);
        func_0200457c(0);
    }
}

int func_ov095_022999b0(struct UnkStruct_022999b0 *p, unsigned int mask)
{
    if ((p->unk_14 & mask) != 0) {
        return 1;
    }
    return 0;
}

void func_ov095_022999a8(unsigned short *p0, int p1)
{
    p0[10] = (p0[10] | p1);
}

void func_ov095_022999a0(char *p, int v)
{
    *(unsigned short *) (p + 0x14) &= ~v;
}
