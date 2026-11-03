/* insect_draw: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0202d0ec @ 0x0202d0ec, 0xa4 bytes, Thumb
 * func_0202d060 @ 0x0202d060, 0x8c bytes, Thumb
 * func_0202cfa8 @ 0x0202cfa8, 0xb8 bytes, Thumb
 * func_0202cef4 @ 0x0202cef4, 0xb4 bytes, Thumb
 */

#include "types.h"

typedef struct Entry {
    const u8 *rec;
    u8 count;
    u8 pad_05[3];
} Entry;

typedef struct St {
    int unk_00;
    int unk_04;
} St;

extern int func_020644cc(int);
extern int func_0202d1cc(u16 *, int *, int *, int, void *, int, int, u8, u8);
extern void MI_CpuCopy8(void *, void *, int);
extern void func_0202d3d4(int *, int *);
extern int func_0202d6e4(void *, int);
extern int func_0202d1a8(int, int, int, int, int, int *, int);
extern int data_020c8948;
extern unsigned char data_021c1d10[];
extern void func_0209e474(St *);
extern int func_02061798(u8);
extern Entry *func_020617d8(int);
extern void MI_CpuFill8(void *, int, int);
extern int func_0202d2a0(u16 *, int *, int, const u8 *, int, int *, int);

int func_0202d0ec(u16 *a, int lo, int hi, u8 d, u8 e5, u8 f)
{
    void *tbl;
    int o1;
    int o2;
    u8 mask;
    int cnt;
    int i;
    int k;

    tbl = (void *) func_020617d8(f - 1);
    if (tbl != 0) {
        mask = 0;
        cnt = hi - lo + 1;
        o1 = 0;
        o2 = 0;
        while (lo <= hi) {
            mask |= 1 << lo;
            lo++;
        }
        while (cnt > 0) {
            k = func_020644cc(cnt);
            for (i = 0; i < 5; i++) {
                if ((mask >> i) & 1) {
                    if (k == 0) {
                        if (func_0202d1cc(a, &o1, &o2, i, tbl, 0, 0, d, e5) != 0) {
                            return 1;
                        }
                        mask &= ~(1 << i);
                        break;
                    }
                    k--;
                }
            }
            cnt--;
        }
    }
    return 0;
}

int func_0202d060(int a, int *b, int c, int d, unsigned char *e)
{
    int res;
    int varA;
    int varB;
    int i;
    int r4;
    int ok;
    int buffer[4];
    int result = 0;

    res = (int) func_020617d8(e[4] - 1);
    if (res != 0) {
        varB = 0;
        MI_CpuCopy8(&data_020c8948, data_021c1d10, 5);
        func_0202d3d4(buffer, &varB);

        i = 0;
        varA = i;
        while (i < 5) {
            r4 = func_0202d6e4(data_021c1d10, 5);
            if (r4 < 0 || r4 >= 5) {
                break;
            }
            ok = func_0202d1a8(a, c, d, r4, res, buffer, varB);
            if (ok == 1) {
                *b = r4;
                result = 1;
                break;
            } else {
                data_021c1d10[r4] = varA;
                i++;
            }
        }
    }
    return result;
}

void func_0202cfa8(u16 *p)
{
    St st;
    u8 flags[5];
    int out2;
    int a4;
    int buf[4];
    Entry *tbl;
    Entry *e;
    int n;
    int i;
    int k;
    int idx;
    unsigned int ok;
    u16 h;

    st.unk_00 = 0;
    st.unk_04 = 0;
    n = 5;
    out2 = 0;
    func_0209e474(&st);
    idx = func_02061798(((u8 *) &st)[2]);
    tbl = func_020617d8(((u8 *) &st)[4] - 1);
    if (tbl != 0 && idx >= 0 && idx < 6) {
        a4 = 0;
        e = &tbl[idx];
        MI_CpuFill8(flags, a4, n);
        func_0202d3d4(buf, &a4);
        while (n > 0) {
            k = func_020644cc(n);
            for (i = 0; i < 5; i++) {
                if (flags[i] == 0) {
                    if (k == 0) {
                        func_0202d2a0(p, &out2, i, e->rec, e->count, buf, a4);
                        flags[i] = 1;
                        break;
                    }
                    k--;
                }
            }
            ok = 0;
            h = *p;
            if (h >= 0x12b0 && h <= 0x12e7) {
                ok = 1;
            }
            if (ok != 0) {
                break;
            }
            n--;
        }
    }
}

int func_0202cef4(u16 *p, int j, int last, int a4)
{
    int v;
    int b1;
    Entry *tbl;
    const u8 *e;
    int idx;
    int prev;
    int m;
    int cnt;
    int d;
    int prev0;
    int t;
    unsigned int ok;
    u16 h;
    ok = 0;
    h = *p;
    if ((h >= 0x12b0) && (h <= 0x12e7)) {
        ok = 1;
    }
    if (ok > 0) {
        tbl = func_020617d8(a4 - 1);
        if (tbl != 0) {
            prev = 6;
            ok = 0;
            h = *p;
            if ((h >= 0x12b0) && (h <= 0x12e7)) {
                ok = 1;
            }
            if (ok > 0) {
                t = h - 0x12b0;
            } else {
                t = -1;
            }
            v = (u8) t;
            while (j <= last) {
                idx = func_02061798((u8) j);
                if (idx != prev) {
                    e = (const u8 *) tbl[idx].rec;
                    if (e != 0) {
                        prev0 = 0;
                        m = 0;
                        cnt = tbl->count;
                        while (m < cnt) {
                            b1 = e[1];
                            d = b1 - prev0;
                            if ((v == e[0]) && (d > 0)) {
                                return 1;
                            }
                            prev0 = b1;
                            e += 2;
                            m++;
                        }
                    }
                    prev = idx;
                }
                j++;
            }
        }
    }
    return 0;
}
