/* func_ov003_0221bac8 @ 0x0221bac8, 0xd4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096174(void *self);
extern int func_ov009_02264c90(void *self);
extern int func_ov009_022631b4(void *self);
extern int func_ov009_0226321c(void *self, void *local, short *shortp);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern int func_020b65c4(void);
extern void func_020b5ea0(int a, int b, void *c, int d, int e, int f, int g);
extern int func_020310c8(int a);

typedef struct {
    void *unk_00;
    int unk_04;
    int unk_08;
} LocalData;

void func_ov003_0221bac8(void *self)
{
    unsigned int threshold;
    short localShort;
    LocalData local;
    int a, b;
    unsigned char temp;

    if (func_02096174(self)) {
        *(unsigned short *) ((char *) self + 0x2b8) += 1;
    }

    threshold = (func_ov009_02264c90(self) == 2) ? 0x14 : 0xF;
    if (func_ov009_02264c90(self) == 1) {
        threshold += 0xC;
    }

    if (*(unsigned short *) ((char *) self + 0x2b8) < threshold) {
        return;
    }

    threshold = func_ov009_022631b4(self);
    if (func_ov009_0226321c(self, &local, &localShort) == 0) {
        return;
    }

    if (func_020b6098(func_020b5e10(), threshold) == 0) {
        return;
    }

    local.unk_04 = func_020310c8(0);
    local.unk_08 += 0x1000;

    a = func_020b5e10();
    b = func_020b65c4();
    func_020b5ea0(a, b, &local, 0x0f000000, (short) (localShort + 0x8000), *(int *) ((char *) self + 0x22c),
                  *(int *) ((char *) self + 0x230));

    temp = *(unsigned char *) ((char *) self + 0x236);
    *(unsigned char *) ((char *) self + 0x236) = (temp & ~1) | 1;
}
