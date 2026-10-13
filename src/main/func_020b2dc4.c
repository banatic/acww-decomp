/* func_020b2dc4 @ 0x020b2dc4, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020b2dc4 {
    unsigned short id;
} UnkStruct_020b2dc4;

extern int func_02037d64(void *, int);
extern UnkStruct_020b2dc4 *func_02037e0c(void *, unsigned int, unsigned int, int);
extern int func_02037e44(void *, u16 *, unsigned int, unsigned int, int);

int func_020b2dc4(void *self, int arg1, int arg2)
{
    int count;
    unsigned int y;
    unsigned int start;
    int zero;
    int zero2;
    unsigned int x;
    UnkStruct_020b2dc4 *e;
    u16 local;

    count = 0;
    if (self != 0) {
        if (func_02037d64(self, 0xe0) != 0 || func_02037d64(self, 0x10) != 0) {
            return 0;
        }
        y = 0;
        start = 0;
        zero2 = 0;
        zero = 0;
        for (; y < 0x10; y++) {
            for (x = start; x < 0x10; x++) {
                e = func_02037e0c(self, x, y, zero);
                if (e != 0 && e->id == 0x500a) {
                    if (arg1 == count) {
                        local = (u16) arg2;
                        if (func_02037e44(self, &local, x, y, zero2) != 0) {
                            return 1;
                        }
                    }
                    count++;
                }
            }
        }
    }
    return 0;
}
