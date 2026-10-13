/* func_ov004_0221cf00 @ 0x0221cf00, 0xe0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0207f1c8(int a);
extern int func_0209b5ec(int a);
extern unsigned int func_0209c330(int a);
extern int func_0204bcdc(u16 *w);

int func_ov004_0221cf00(char *s, u16 *w)
{
    char *p;
    unsigned int k;
    int r;
    int t;
    p = (char *) *(int *) (s + 0x1a4);
    if (p != 0) {
        if (*(int *) (p + 0x830) != 0) {
            k = func_0209c330(func_0209b5ec(func_0207f1c8(*(int *) (p + 0x830))));
            r = 0;
            switch (k) {
                case 0:
                    if (*w >= 0x12b0 && *w <= 0x12e7) {
                        r = 1;
                    }
                    break;
                case 1:
                    if (*w >= 0x12e8 && *w <= 0x131f) {
                        r = 1;
                    }
                    break;
                case 2:
                    if (*w >= 0x450c && *w <= 0x45db) {
                        r = 1;
                    }
                    break;
                case 3:
                    if (*w >= 0x11a8 && *w <= 0x12a7) {
                        r = 1;
                    }
                    break;
                case 4:
                    if (func_0204bcdc(w) != 0) {
                        t = r;
                        if (*w >= 0x450c && *w <= 0x45db) {
                            t = 1;
                        }
                        if (t == 0) {
                            r = 1;
                        }
                    }
                    break;
            }
            return r;
        }
    }
    return 0;
}
