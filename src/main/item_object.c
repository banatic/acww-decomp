/* item_object: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209bbb4 @ 0x0209bbb4, 0x38 bytes, Thumb
 * func_0209bba8 @ 0x0209bba8, 0xc bytes, Thumb
 * func_0209bba0 @ 0x0209bba0, 0x8 bytes, Thumb
 * func_0209bb90 @ 0x0209bb90, 0xe bytes, Thumb
 * func_0209bb88 @ 0x0209bb88, 0x8 bytes, Thumb
 * func_0209bb74 @ 0x0209bb74, 0x12 bytes, Thumb
 * func_0209bb70 @ 0x0209bb70, 0x4 bytes, Thumb
 * func_0209bb68 @ 0x0209bb68, 0x6 bytes, Thumb
 */

typedef struct {
    unsigned char pad_00[0xb];
    unsigned char unk_0B;
} UnkStruct_0209bb90;

struct UnkStruct0209bb74 {
    unsigned char pad_00[11];
    unsigned char unk_0B;
};

extern int func_0209bc94(unsigned int param);

int func_0209bbb4(unsigned int param)
{
    int result = 4;
    if (func_0209bc94(param) == 1) {
        if (param < 19) {
            if (param < 11) {
                result = 0;
            } else {
                result = 1;
            }
        } else {
            if (param < 20) {
                result = 2;
            } else if (param < 21) {
                result = 3;
            }
        }
    }
    return result;
}

int func_0209bba8(unsigned char *r0)
{
    return func_0209bbb4((unsigned char) r0[0xa]);
}

int func_0209bba0(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[11] << 27)) >> 27);
}

void func_0209bb90(UnkStruct_0209bb90 *p, int val)
{
    p->unk_0B = (p->unk_0B & ~0x1f) | (val & 0x1f);
}

int func_0209bb88(unsigned char *p0)
{
    return (int) ((unsigned int) ((p0[11] << 24)) >> 29);
}

void func_0209bb74(struct UnkStruct0209bb74 *r0, unsigned int r1)
{
    r0->unk_0B = (r0->unk_0B & ~0xe0U) | ((r1 & 7U) << 5);
}

int func_0209bb70(int p0)
{
    return ((int) (p0) + (8));
}

void func_0209bb68(unsigned short *d, unsigned short *s)
{
    d[4] = *s;
}
