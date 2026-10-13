/* func_0202cfa8 @ 0x0202cfa8, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
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

extern void func_0209e474(St *);
extern int func_02061798(u8);
extern Entry *func_020617d8(int);
extern void MI_CpuFill8(void *, int, int);
extern void func_0202d3d4(int *, int *);
extern int func_020644cc(int);
extern int func_0202d2a0(u16 *, int *, int, const u8 *, int, int *, int);

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
