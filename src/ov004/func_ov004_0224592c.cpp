/* func_ov004_0224592c @ 0x0224592c, 0x260 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern "C" {
extern u8 data_021c75b8, data_021fbdd8, data_021fbddc;
extern char *data_020ccf94;
extern u16 data_021fbe40[];
extern void func_ov004_02245cf4(char *, int);
extern int func_ov004_02230d94(void);
extern void func_ov004_02230d70(void);
extern void func_0208ffc0(void);
extern int func_02096190(int);
}
static inline int active(void)
{
    if (data_021c75b8 == 2) {
        return 1;
    }
    return 0;
}
static inline int cancelled(void)
{
    if (data_021fbdd8 && data_021fbddc) {
        return 1;
    }
    return 0;
}
extern "C" void func_ov004_0224592c(char *self)
{
    char *context;
    u8 selection;
    if (!active()) {
        return;
    }
    context = data_020ccf94;
    if (*(int *) (context + 0x68) != 4) {
        func_ov004_02245cf4(self, 3);
        return;
    }
    if (func_ov004_02230d94()) {
        func_ov004_02245cf4(self, 0);
        return;
    }
    if (cancelled()) {
        func_0208ffc0();
        func_ov004_02245cf4(self, 1);
        return;
    }
    if (*(u8 *) (self + 0x31d)) {
        if (data_021fbe40[1] & 0x80) {
            *(u8 *) (self + 0x31d) = 0;
        } else if ((data_021fbe40[1] & 0x10) || (data_021fbe40[1] & 0x20)) {
            selection = *(u8 *) (self + 0x31c);
            if (data_021fbe40[1] & 0x10) {
                selection = 1;
            } else if (data_021fbe40[1] & 0x20) {
                selection = 0;
            }
            if (func_02096190(selection)) {
                *(u8 *) (self + 0x31d) = 0;
                *(u8 *) (self + 0x31c) = selection;
            }
        }
    } else {
        selection = *(u8 *) (self + 0x31c);
        switch (selection) {
            case 0:
                if (data_021fbe40[1] & 0x10) {
                    selection++;
                } else if (data_021fbe40[1] & 0x80) {
                    selection += 2;
                    if (!func_02096190(selection)) {
                        selection++;
                    }
                } else if (data_021fbe40[1] & 0x40) {
                    *(u8 *) (self + 0x31d) = 1;
                }
                break;
            case 1:
                if (data_021fbe40[1] & 0x20) {
                    selection--;
                } else if (data_021fbe40[1] & 0x80) {
                    selection += 2;
                    if (!func_02096190(selection)) {
                        selection--;
                    }
                } else if (data_021fbe40[1] & 0x40) {
                    *(u8 *) (self + 0x31d) = 1;
                }
                break;
            case 2:
                if (data_021fbe40[1] & 0x10) {
                    selection++;
                } else if (data_021fbe40[1] & 0x40) {
                    selection -= 2;
                    if (!func_02096190(selection)) {
                        selection++;
                        if (!func_02096190(selection)) {
                            *(u8 *) (self + 0x31d) = 1;
                        }
                    }
                }
                break;
            case 3:
                if (data_021fbe40[1] & 0x20) {
                    selection--;
                } else if (data_021fbe40[1] & 0x40) {
                    selection -= 2;
                    if (!func_02096190(selection)) {
                        selection--;
                        if (!func_02096190(selection)) {
                            *(u8 *) (self + 0x31d) = 1;
                        }
                    }
                }
                break;
        }
        if (func_02096190(selection)) {
            *(u8 *) (self + 0x31c) = selection;
        }
    }
    if ((data_021fbe40[1] & 8) || (data_021fbe40[1] & 1)) {
        if (*(u8 *) (self + 0x31d)) {
            func_ov004_02230d70();
        } else {
            *(int *) (context + 0x68) = *(u8 *) (self + 0x31c);
            func_ov004_02245cf4(self, 3);
        }
    }
}
