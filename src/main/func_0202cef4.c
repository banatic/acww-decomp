/* func_0202cef4 @ 0x0202cef4, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Entry {
    const u8 *rec;
    u8 count;
    u8 pad_05[3];
} Entry;
extern Entry *func_020617d8(int);
extern int func_02061798(u8);
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
