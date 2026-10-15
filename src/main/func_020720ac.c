/* func_020720ac @ 0x020720ac, 0xc0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

// Built at -O1,s.

extern u8 data_020e54a8;

extern int func_020984fc(int);
extern int func_0209985c(int);
extern int func_02071568(u8, int);
extern int func_020b65c4(void);
extern int func_020714e0(int);
extern int func_02072614(void);
extern void func_020727a4(int, int);
extern int func_020b6660(void);
extern int func_ov003_02220174(int);
extern int func_ov003_0221c4bc(void *);

int func_020720ac(int mode, int b)
{
    int tested_value0;
    void *condition_value0;
    int v;
    int t;

    switch (mode) {
        case 0:
        case 9:
            if ((tested_value0 = (int) (func_020984fc(0)))) {
                v = func_0209985c(tested_value0);
                if (v != -1) {
                    func_02071568((u8) (v & 3), b);
                }
            }
            return 1;
        case 4:
            t = (data_020e54a8 == 1);
            if (t) {
                if (func_020b65c4() == 0xa) {
                    func_020714e0(b);
                    func_020727a4(func_02072614(), b & 7);
                }
            }
            return 1;
        case 5:
            t = (data_020e54a8 == 0);
            if (t) {
                if (func_020b6660()) {
                    if ((condition_value0 = (void *) (func_ov003_02220174(0x500b)))) {
                        func_ov003_0221c4bc(condition_value0);
                    }
                }
            }
            return 1;
    }
    return 0;
}
