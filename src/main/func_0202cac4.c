/* func_0202cac4 @ 0x0202cac4, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Slot {
    void *p;
} Slot;
typedef struct St {
    int unk_00;
    int unk_04;
} St;

extern void func_0209e474(St *);
extern int func_0204fafc(u8);
extern Slot **func_0204fc3c(u8, int);
extern int func_0204fb08(u8);
extern void MI_CpuFill8(void *, int, int);
extern int func_020644cc(int);
extern int func_0202cd78(u16 *, int *, int, Slot *);

void func_0202cac4(u16 *p)
{
    St st;
    u8 flags[5];
    int out;
    Slot **tbl;
    Slot *e;
    unsigned int idx;
    int n;
    int i;
    int k;
    u8 t3;
    u8 t4;
    unsigned int ok;
    u16 h;

    st.unk_00 = 0;
    st.unk_04 = 0;
    n = 5;
    func_0209e474(&st);
    t4 = ((u8 *) &st)[4];
    t3 = ((u8 *) &st)[3];
    tbl = func_0204fc3c(t4, func_0204fafc(t3));
    if (tbl != 0 && *tbl != 0) {
        idx = func_0204fb08(((u8 *) &st)[2]);
        if (idx < 3) {
            e = *tbl + idx;
            MI_CpuFill8(flags, 0, n);
            while (n > 0) {
                k = func_020644cc(n);
                for (i = 0; i < 5; i++) {
                    if (flags[i] == 0) {
                        if (k == 0) {
                            func_0202cd78(p, &out, i, e);
                            flags[i] = 1;
                            break;
                        }
                        k--;
                    }
                }
                ok = 0;
                h = *p;
                if (h >= 0x12e8 && h <= 0x131f) {
                    ok = 1;
                }
                if (ok != 0) {
                    break;
                }
                n--;
            }
        }
    }
}
