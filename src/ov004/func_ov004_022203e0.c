/* func_ov004_022203e0 @ 0x022203e0, 0xec bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef void (*VF)(char *);

extern int func_0201c2a4(char *self, int n);
extern void func_02016108(char *a, int b);
extern void func_ov004_02221550(char *self, int n);
extern void func_ov004_0223ce84(void);
extern int func_ov004_0223cdc0(void);
extern void func_020b23d4(void);
extern void func_02030864(int a);
extern void func_ov004_0223d33c(void);
extern void func_0209e474(char *p);
extern int *func_02095794(int n);
extern int func_02030818(int *v);
extern void func_020307f8(void);

void func_ov004_022203e0(char *self, int n)
{
    // DECLS
    int t[3];
    char *o;
    int *p;
    // ENDDECLS

    switch (n) {
        case 1:
            o = self + 0x918;
            (*(VF *) (*(char **) o + 8))(o);
            func_02016108(self + 0x918, func_0201c2a4(self, 4));
            if (*(u8 *) (self + 0xac8) == 5 || *(u8 *) (self + 0xac8) == 3) {
                func_ov004_02221550(self, 7);
            } else {
                func_ov004_02221550(self, 6);
            }
            if (*(u8 *) (self + 0xac8) == 0) {
                func_ov004_0223ce84();
                *(int *) (self + 0xae4) = func_ov004_0223cdc0();
                func_020b23d4();
                func_02030864(0);
                func_ov004_0223d33c();
                func_0209e474(self + 0xad0);
            }
            break;
        case 0:
            o = self + 0x918;
            (*(VF *) (*(char **) o + 8))(o);
            func_02016108(self + 0x918, func_0201c2a4(self, 4));
            func_ov004_02221550(self, 6);
            break;
        case 8:
            if (*(u8 *) (self + 0xac8) == 6) {
                p = func_02095794(4);
                t[0] = p[0];
                t[1] = p[1];
                t[2] = p[2];
                if (func_02030818(t) != 0) {
                    func_020307f8();
                    break;
                }
            }
            func_ov004_02221550(self, 3);
            break;
    }
}
