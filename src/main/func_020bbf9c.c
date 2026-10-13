/* func_020bbf9c @ 0x020bbf9c, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O3,s
 */

#include "types.h"

extern int data_021f8ad4;
extern int data_021f8ad8;
extern int *data_020e60c0[];
extern u8 data_021f6cf8[];

void func_020bbf9c(int t0, int t1, const u8 *p2, const u8 *p3)
{
    u8 *out;
    int e0;

    out = data_021f6cf8;
    if (data_021f8ad8 != data_021f8ad4) {
        int i;
        int d0;
        int d1;
        int ia;
        int ib;
        int sa;
        int sb;

        i = 0;
        d0 = 0x1000 - t0;
        d1 = 0x1000 - t1;
        for (; i < 2; i++) {
            ia = data_020e60c0[data_021f8ad4][i];
            sa = d0;
            sa = p2[ia] * sa;
            sa = sa + p3[ia] * t0;
            sa = (u16) (sa >> 12);
            ib = data_020e60c0[data_021f8ad8][i];
            sa = d1 * sa;
            sb = d0;
            sb = p2[ib] * sb;
            sb = sb + p3[ib] * t0;
            sb = (u16) (sb >> 12);
            sb = t1 * sb;
            *out = (u8) ((sa + sb) >> 12);
            out++;
        }
    } else {
        int k;
        int ic;
        int s;

        k = 0;
        e0 = 0x1000 - t0;
        for (; k < 2; k++) {
            ic = data_020e60c0[data_021f8ad4][k];
            s = p2[ic] * e0;
            s = s + p3[ic] * t0;
            *out = (u8) (s >> 12);
            out++;
        }
    }
}
