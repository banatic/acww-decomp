/* func_02076c84 @ 0x02076c84, 0xbc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02076c84 {
    u16 unk_00;
    u16 unk_02;
} UnkStruct_02076c84;

extern void *data_020ccf94;
extern void func_020736bc(void *g, int *v, int a0, int a3);
extern void func_0209646c(int *v, UnkStruct_02076c84 *w, int *sel);
extern void func_020955e0(u16 *p, int sel, int a3);
extern int func_020984fc(int a3);
extern u16 *func_02099728(void);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_02062148(u16 *p);
extern void func_0209971c(int h, u16 *p);
extern void func_02095694(int n, int a3);

void func_02076c84(int a0, int a1, int a2, int a3)
{
    UnkStruct_02076c84 w;
    int v;
    int sel;
    int h;
    u16 *q;
    int r;
    int n;
    unsigned int ok;

    func_020736bc(data_020ccf94, &v, a0, a3);
    func_0209646c(&v, &w, &sel);
    w.unk_02 = w.unk_00;
    switch (sel) {
        case 0:
        case 1:
        case 2:
            func_020955e0(&w.unk_02, sel, a3);
            break;
        case 3:
            h = func_020984fc(a3);
            q = func_02099728();
            if (func_0204bcdc(&w.unk_02) != 0) {
                r = func_0204bc64(&w.unk_02);
                ok = (r == func_0204bc64(q)) ? 1 : 0;
            } else {
                ok = (w.unk_02 == *q) ? 1 : 0;
            }
            if (ok == 0) {
                n = func_02062148(&w.unk_02);
                func_0209971c(h, &w.unk_02);
                func_02095694(n + 1, a3);
            }
            break;
    }
}
