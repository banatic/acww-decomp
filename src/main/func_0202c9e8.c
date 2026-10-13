/* func_0202c9e8 @ 0x0202c9e8, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Entry {
    const u8 *rec;
    u8 count;
    u8 pad_05[3];
} Entry;
typedef struct Slot {
    Entry *e;
} Slot;

extern int func_0204fafc(u8);
extern Slot **func_0204fc3c(int, int);
extern int func_0204fb08(u8);

int func_0202c9e8(u16 *p, int j, int last, int d4, u8 p5)
{
    Slot **tbl;
    int v;
    int idx;
    Entry *e;
    const u8 *rec;
    int prev;
    int m;
    int i;
    int cnt;
    unsigned int b0;
    int t;
    unsigned int ok;
    u16 h;

    ok = 0;
    h = *p;
    if (h >= 0x12e8 && h <= 0x131f) {
        ok = 1;
    }
    if (ok > 0) {
        tbl = func_0204fc3c(d4, func_0204fafc(p5));
        if (tbl != 0 && *tbl != 0) {
            prev = 3;
            ok = 0;
            h = *p;
            if (h >= 0x12e8 && h <= 0x131f) {
                ok = 1;
            }
            if (ok > 0) {
                t = h - 0x12e8;
            } else {
                t = -1;
            }
            v = (u8) t;
            while (j <= last) {
                idx = func_0204fb08((u8) j);
                if (idx != prev) {
                    e = (*tbl)[idx].e;
                    if (e != 0) {
                        for (m = 0; m < 2; m++) {
                            rec = e->rec;
                            if (rec != 0) {
                                cnt = e->count;
                                if (cnt != 0) {
                                    for (i = 0; i < cnt; i++) {
                                        b0 = rec[0];
                                        if (b0 < 0x38 && b0 == v && rec[2] != 0) {
                                            return 1;
                                        }
                                        rec += 3;
                                    }
                                }
                            }
                            e += 1;
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
