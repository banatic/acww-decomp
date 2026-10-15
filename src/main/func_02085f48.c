/* func_02085f48 @ 0x02085f48, 0xe4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02085f48 {
    u8 *data;
    unsigned int w;
    unsigned int h;
};

extern struct UnkStruct_02085f48 *func_0204e414(void);
extern u16 *func_02037e0c(u8 *, int, int, int);
extern int func_0204bcdc(u16 *);
extern int func_0204bc64(u16 *);
extern int func_02037e44(u8 *, u16 *, int, int, int);

void func_02085f48(void)
{
    struct UnkStruct_02085f48 *m;
    u8 *cell;
    u16 *p;
    u16 buf[2];
    int x;
    int y;
    int col;
    int row;
    int ok;
    int a;

    m = func_0204e414();
    if (m == 0) {
        return;
    }
    for (y = 1; y < 5; y++) {
        for (x = 1; x < 5; x++) {
            if (x < m->w && y < m->h && m->data != 0) {
                cell = m->data + 0x28 * (x + y * m->w);
            } else {
                cell = 0;
            }
            if (cell == 0) {
                continue;
            }
            p = func_02037e0c(cell, 0, 0, 0);
            if (p == 0) {
                continue;
            }
            for (row = 0; row < 0x10; row++) {
                for (col = 0; col < 0x10; col++) {
                    if (func_0204bcdc(p) != 0) {
                        buf[1] = 0x1568;
                        a = func_0204bc64(p);
                        ok = (a == func_0204bc64(&buf[1])) ? 1 : 0;
                    } else {
                        ok = (*p == 0x1568) ? 1 : 0;
                    }
                    if (ok != 0) {
                        buf[0] = 0xfff1;
                        func_02037e44(cell, buf, col, row, 0);
                    }
                    p++;
                }
            }
        }
    }
}
