/* func_ov068_02270b00 @ 0x02270b00, 0x224 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char *func_020961a8(int a);
extern int func_02070070(void);
extern void func_ov003_0223597c(void *out, int val);
extern fx32 FX_MulFunc(fx32 a, fx32 b);
extern fx32 FX_Div(fx32 n, fx32 d);
extern int func_0200322c(void *a, void *b);
extern int func_020ea990(void *a, void *b);
extern void func_020e8870(void *buf, int val, int k);
extern void func_ov068_02270a64(void *a, void *b, int c);

void func_ov068_02270b00(u8 *self)
{
    char *ret;
    int *f204;
    int sum;
    u8 *f256;
    char *retOff;
    int local2;
    int local3;
    int startVal;
    s16 buf;
    int vecA[3];
    int vecB[3];

    ret = func_020961a8(4);
    f204 = (int *) (self + 0x204);

    startVal = *(s16 *) (self + 0x23a);
    buf = (s16) startVal;

    {
        s16 f232 = *(s16 *) (self + 0x232);
        f256 = self + 0x256;

        if (f232 > 0) {
            *(s16 *) (self + 0x232) = f232 - 1;
        } else if (func_02070070() != 0) {
            buf = buf + 0x1554;
            *(s16 *) (self + 0x23a) = buf;
            func_ov003_0223597c(vecA, buf);

            f204[0] += FX_MulFunc(0x23000, vecA[0]);
            f204[2] += FX_MulFunc(0x23000, vecA[2]);

            func_ov068_02270a64(self + 0x210, self + 0x50, startVal - buf);
            *f256 = 9;
            return;
        }
    }

    if (ret == 0) {
        return;
    }

    retOff = ret + 0x5c;
    local2 = func_0200322c(f204, retOff);
    sum = *(u8 *) (self + 0x257) + *(int *) (self + 0x21c);
    local3 = func_020ea990(f204, retOff);

    if (local3 < 0x1000) {
        self[0x251] = 3;
        *(s16 *) (self + 0x242) = 0;
        return;
    }

    if (*f256 != 0) {
        *f256 -= 1;
        func_020e8870(&buf, local2, 0xe38);
    } else if (sum < 0xfa) {
        func_020e8870(&buf, local2, 0x93e);
    } else if (sum < 0x104) {
        func_020e8870(&buf, local2, 0x7d2);
    } else {
        func_020e8870(&buf, local2, 0x666);
    }

    {
        int d = (local2 - buf) / 182;
        if (d < 0) {
            d = -d;
        }
        if ((u8) d > 15 && sum > 0xb4) {
            sum -= 2;
            *(int *) (self + 0x21c) = sum;
        } else if (sum < 0x122) {
            sum += 7;
            *(int *) (self + 0x21c) = sum;
        }
    }

    *(s16 *) (self + 0x23a) = buf;

    func_ov003_0223597c(vecB, buf);

    if (local3 > 0xe000) {
        int r6 = sum << 12;
        f204[0] += FX_Div(FX_MulFunc(r6, vecB[0]), 0x3800);
        f204[2] += FX_Div(FX_MulFunc(r6, vecB[2]), 0x3800);
    } else {
        int r6 = sum << 12;
        f204[0] += FX_Div(FX_MulFunc(r6, vecB[0]), 0x5000);
        f204[2] += FX_Div(FX_MulFunc(r6, vecB[2]), 0x5000);
    }

    func_ov068_02270a64(self + 0x210, self + 0x50, (startVal - buf) * 5);
}
