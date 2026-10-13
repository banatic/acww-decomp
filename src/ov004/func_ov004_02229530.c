/* func_ov004_02229530 @ 0x02229530, 0xc8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *data_020ccf94;
extern int func_02073908(void *, int);
extern int func_02008258(void *, int);
extern int func_02051eac(void);
extern void func_0200d4e8(void *, int, int, int);
extern void func_ov004_022294a0(void *, int, int);
extern void func_ov004_02229010(void *, int, int);
extern void func_ov004_02229258(void *, int, int);

void func_ov004_02229530(char *self)
{
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) == 0) {
        *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
    } else {
        switch (func_02051eac()) {
            case 0:
                break;
            case 2:
                *(int *) (self + 0x7fc) = func_02008258(self, *(int *) (self + 0x7f0));
                func_0200d4e8(self, 3, 1, -1);
                break;
            case 1:
            default: {
                char *a = self + 0x7d4;
                char *b = self + 0x5c;
                if (*(int *) b == *(int *) a && *(int *) (b + 8) == *(int *) (a + 4) &&
                    *(short *) (a + 8) == *(short *) (self + 0x8e)) {
                    switch (*(u8 *) (a + 0xa)) {
                        case 0:
                            func_ov004_022294a0(self, 6, -1);
                            break;
                        case 1:
                            func_ov004_02229010(self, 6, -1);
                            break;
                        case 2:
                            func_ov004_02229258(self, 6, -1);
                            break;
                    }
                }
            } break;
        }
    }
}
