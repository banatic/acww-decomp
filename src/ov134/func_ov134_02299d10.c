/* func_ov134_02299d10 @ 0x02299d10, 0x1bc bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern unsigned int func_ov134_0229b884(void *s, int param);
extern void func_ov134_0229b808(void *s, int a, int b);
extern int func_0209de24(unsigned char a, unsigned char b);
extern void func_ov134_0229a96c(void *s, int a, int b);
extern void func_0209e140(void *addr, int val);
extern void func_0209e29c(void *addr, int val);
extern int func_ov134_022995c0(void *s, int param);
extern int func_0209e3ac(void *a, void *b, int len);
extern void MI_CpuCopy8(void *a, void *b, int len);
extern void func_ov134_0229b890(void *s, int val);

typedef struct UnkStruct_02299d10 {
    u8 pad_00[0x88];
    u32 unk_88;
    u8 pad_8C[0xa0 - 0x8c];
    u8 unk_A0;
    u8 pad_A1[0xa5 - 0xa1];
    u8 unk_A5;
    u8 pad_A6[0xad - 0xa6];
    u8 unk_AD;
    u8 pad_AE[0xb2 - 0xae];
    u8 unk_B2;
    u8 pad_B3[0xb8 - 0xb3];
    u8 unk_B8;
    u8 pad_B9[0xbb - 0xb9];
    u8 unk_BB;
    u8 unk_BC;
    u8 unk_BD;
    u8 pad_BE[0xc8 - 0xbe];
    u8 unk_C8;
    u8 pad_C9[0xd0 - 0xc9];
    u8 unk_D0;
} UnkStruct_02299d10;

int func_ov134_02299d10(UnkStruct_02299d10 *s)
{
    u16 flag = 0;
    unsigned int t0;

    t0 = func_ov134_0229b884(s, s->unk_A5);
    func_ov134_0229b808(s, s->unk_A5, s->unk_AD);

    flag |= (1 << s->unk_A5);

    {
        int tmp = func_0209de24(s->unk_BD, s->unk_BC);
        if (tmp < (int) s->unk_BB) {
            s->unk_BB = (u8) tmp;
            flag |= 4;
        }
    }

    if (s->unk_A5 <= 2) {
        func_ov134_0229a96c(s, 5, 3);
        flag |= 0x20;
    }

    {
        int n6 = 0;

        if (s->unk_A5 == 3 && s->unk_A0 == 1) {
            u8 b2 = s->unk_B2;
            if (t0 < b2) {
                if (s->unk_AD >= b2) {
                    func_0209e140(&s->unk_B8, 1);
                    n6 = -1;
                }
            } else {
                if (s->unk_AD < b2) {
                    func_0209e29c(&s->unk_B8, 1);
                    n6 = 1;
                }
            }
            if (n6 != 0) {
                flag |= 0x27;
            }
        }

        if (func_ov134_022995c0(s, 0x80) != 0) {
            if (func_0209e3ac(&s->unk_C8, &s->unk_B8, 0x3f) == 1) {
                MI_CpuCopy8(&s->unk_C8, &s->unk_B8, 8);
                flag = 0xffff;
            }
        }

        if (func_ov134_022995c0(s, 0x40) != 0) {
            if (func_0209e3ac(&s->unk_D0, &s->unk_B8, 0x3f) == -1) {
                MI_CpuCopy8(&s->unk_D0, &s->unk_B8, 8);
                flag = 0xffff;
            }
        }

        {
            u8 i;
            for (i = 0; i <= 5; i++) {
                if ((flag & (1 << i)) != 0) {
                    func_ov134_0229b890(s, i);
                }
            }
        }

        if ((u8) (s->unk_A5 + 0xfd) <= 1) {
            if (t0 == s->unk_AD) {
                return 0;
            } else {
                int v = func_ov134_0229b884(s, 4);
                int w = func_ov134_0229b884(s, 3);
                s->unk_88 = v + w * 0x3c;
                s->unk_88 += n6 * 0x5a0;
                return 1;
            }
        }
        return 0;
    }
}