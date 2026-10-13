/* func_0204a848 @ 0x0204a848, 0x380 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Stats {
    u8 pad_00[4];
    u8 cnt[2][2];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    int unk_10;
    int unk_14;
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[2];
    int unk_20;
} Stats;

extern u16 *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204f2b8(int, int, int, int, int);
extern int func_0204b910(u16 *);
extern void func_0204b038(Stats *);

void func_0204a848(Stats *pd, int a1, int a2, int a3)
{
    int j;
    int i;
    int n;
    u16 *p;
    int ok;
    int ok3;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            pd->cnt[j][i] = 0;
        }
    }
    pd->unk_08 = 0;
    pd->unk_0A = 0;
    pd->unk_0C = 0;
    pd->unk_0E = 0;
    pd->unk_20 = 0;
    pd->unk_10 = -1;
    pd->unk_14 = -1;
    pd->unk_18 = 0;
    pd->unk_1A = 0;
    pd->unk_1C = 0;
    pd->unk_1D = 0;

    p = func_0204f5e0(a1, a2, a3, 0, 0, 0);

    for (n = 0; n < 0x100; p++, n++) {
        switch ((*p & 0xf000) >> 12) {
            case 0:
                if ((*p >= 0x26 && *p <= 0x2a) || (*p >= 0x5d && *p <= 0x61) || (*p >= 0x2f && *p <= 0x56) ||
                    (*p >= 0x57 && *p <= 0x5b) || (*p >= 0x66 && *p <= 0x68) || *p == 0x69 || (*p >= 0x6a && *p <= 0x6c) ||
                    *p == 0x6d || (*p >= 0xc8 && *p <= 0xcf)) {
                    pd->cnt[(n & 0xf) >> 3][n >> 7]++;
                    switch (*p) {
                        case 0x66:
                        case 0x6a:
                            pd->unk_20 |= 0x10;
                            break;
                        case 0x67:
                        case 0x6b:
                            pd->unk_20 |= 0x8;
                            break;
                        case 0x68:
                        case 0x6c:
                            pd->unk_20 |= 0x20;
                            break;
                    }
                    ok = 0;
                    if (*p >= 0x26 && *p <= 0x2a) {
                        ok = 1;
                    }
                    if (ok != 0 || (*p >= 0x66 && *p <= 0x68)) {
                        pd->unk_20 |= 0x800;
                        break;
                    }
                    if (*p >= 0x5d && *p <= 0x61) {
                        if (func_0204b910(p) != 0) {
                            pd->unk_20 |= 0x1000;
                            break;
                        }
                    }
                    if (*p == 0x6d) {
                        pd->unk_1A++;
                    }
                    break;
                }
                if (*p >= 0x21 && *p <= 0x24) {
                    pd->unk_08++;
                    break;
                }
                ok = 0;
                if (*p <= 0x1d) {
                    ok = 1;
                }
                if (ok != 0) {
                    switch (*p) {
                        case 0x1b:
                            pd->unk_10 = n % 0x10;
                            pd->unk_14 = n / 0x10;
                            pd->unk_20 = (pd->unk_20 & ~1) | 1;
                            break;
                        case 0x1a:
                            pd->unk_20 |= 0x2;
                            pd->unk_0E++;
                            break;
                        case 0x1c:
                        case 0x1d:
                            pd->unk_0E++;
                            break;
                        default:
                            pd->unk_20 |= 0x4;
                            pd->unk_0E++;
                            break;
                    }
                    break;
                }
                if ((*p >= 0x8a && *p <= 0x8f) || (*p >= 0x90 && *p <= 0x95) || (*p >= 0x96 && *p <= 0x9b) ||
                    (*p >= 0x9c && *p <= 0xa3) || *p == 0xa5 || (*p >= 0x6e && *p <= 0x73) || (*p >= 0x74 && *p <= 0x79) ||
                    (*p >= 0x7a && *p <= 0x7f) || (*p >= 0x80 && *p <= 0x87)) {
                    pd->unk_20 |= 0x4;
                    pd->unk_0E++;
                }
                break;
            case 1:
                if (*p >= 0x1320 && *p <= 0x1322) {
                    pd->unk_0C++;
                    break;
                }
                if (func_0204f2b8(a1, a2, a3, n % 0x10, n / 0x10) == 0) {
                    ok3 = 0;
                    if (*p >= 0x1554 && *p <= 0x155c) {
                        ok3 = 1;
                    }
                    if (ok3 != 0) {
                        pd->unk_1C++;
                        break;
                    }
                    if (*p >= 0x154a && *p <= 0x1553) {
                        pd->unk_20 |= 0x4000;
                        break;
                    }
                    if (*p >= 0x1518 && *p <= 0x151c) {
                        break;
                    }
                    if (*p >= 0x1542 && *p <= 0x1546) {
                        break;
                    }
                    pd->unk_0A++;
                } else {
                    switch (*p) {
                        case 0x1549:
                            pd->unk_1D++;
                            break;
                        case 0x1566:
                            pd->unk_20 |= 0x2000;
                            break;
                    }
                }
                break;
            case 2:
                if (func_0204f2b8(a1, a2, a3, n % 0x10, n / 0x10) == 0) {
                    pd->unk_0A++;
                }
                break;
            case 3:
            case 4:
                pd->unk_0A++;
                break;
        }
    }

    func_0204b038(pd);
}
