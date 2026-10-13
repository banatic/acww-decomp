/* func_02046fa4 @ 0x02046fa4, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

typedef union {
    u16 h;
    u8 b;
} Date;
typedef struct {
    Date unk_00;
    Date d1;
} Buf;

extern int func_02073918(void *a, int b);
extern void func_0209def4(Date *d);
extern int func_02096614(Buf *a, u32 *b, int *c, int d, int e);
extern int func_020b6674(int a);
extern int func_020b6654(int a);
extern int func_0204e414(void);
extern int func_020644cc(int);
extern void func_020470c0(void *a, int b, int c);
extern void *data_020ccf94;
extern u16 data_021c779c;

void func_02046fa4(void *a)
{
    Buf buf;
    u32 v[2];
    int y;
    int found;
    int i;
    int x;
    int r;
    u16 *gp;

    if (func_02073918(data_020ccf94, 0) == 0) {
        return;
    }
    func_0209def4(&buf.d1);
    if (buf.d1.h == data_021c779c) {
        return;
    }
    if (buf.d1.b % 10 != 3) {
        return;
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (func_02096614(&buf, v, &y, -1, i) != 0) {
            if (func_020b6674(buf.unk_00.b) != 0 || func_020b6654(buf.unk_00.b) != 0) {
                if ((y >> 17) == 4) {
                    found = 1;
                    break;
                }
            }
        }
    }
    if (found == 0) {
        x = func_0204e414();
        r = func_020644cc(4);
        func_020470c0(a, x, r);
    }
    gp = &data_021c779c;
    *gp = buf.d1.h;
}
