/* func_0202ce24 @ 0x0202ce24, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Entry {
    const u8 *rec;
    u8 count;
    u8 pad_05[3];
} Entry;

extern int func_0202ceac(int, Entry *);
extern int func_020644cc(int);
extern int func_0209a478(u8);

int func_0202ce24(u16 *out1, int *out2, int key, Entry *e)
{
    const u8 *p;
    int result;
    int c;
    int k;
    int i;
    u16 v;

    p = e->rec;
    result = 0;
    if (p != 0 && e->count != 0) {
        c = func_0202ceac(key, e);
        if (c > 0) {
            k = func_020644cc(c);
            for (i = 0; i < e->count; i++) {
                if (p[2] != 0 && p[0] < 0x38 && key == func_0209a478(p[2])) {
                    if (k == 0) {
                        if (p[0] < 0x38) {
                            v = (u16) (p[0] + 0x12e8);
                        } else {
                            v = 0x12e8;
                        }
                        *out1 = v;
                        *out2 = p[1];
                        result = 1;
                        break;
                    }
                    k--;
                }
                p += 3;
            }
        }
    }
    return result;
}
