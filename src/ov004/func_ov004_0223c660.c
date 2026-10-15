/* func_ov004_0223c660 @ 0x0223c660, 0xa0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void *func_ov004_0223ce84(void);
extern int func_ov004_0223cda4(void *);
extern int func_ov004_02211388(void *);
extern int func_02053de4(int);
extern int func_ov004_0221137c(void *);
extern unsigned int func_ov004_0223c264(int (*)(void *));
extern char *func_ov004_0223c1ec(int (*)(void *), int);
extern void func_ov004_0220d280(void *, int, int);
extern int func_020b65c4(void);
extern void func_02051f4c(int, void *, int);
extern int func_02003348(int, void *, int, int, void *);
extern int func_ov004_02211280(void *);
extern u16 data_ov004_02247f54[];
extern void *data_ov004_022595c0;

int func_ov004_0223c660(void *self)
{
    int k, m;
    u16 kind;
    if (func_ov004_0223cda4(func_ov004_0223ce84()) != 0) {
        k = func_02053de4(func_ov004_02211388(self));
        m = func_ov004_0221137c(self);
        if (k >= 0 && k < 0x30) {
            kind = data_ov004_02247f54[k];
        } else {
            kind = data_ov004_02247f54[0];
        }
        if (k == 0x18 && m == 1) {
            if (func_ov004_0223c264(func_ov004_02211280) >= 4) {
                char *o = func_ov004_0223c1ec(func_ov004_02211280, 0);
                if (o != 0) {
                    func_ov004_0220d280(o + 0x740, 1, 0);
                    func_02051f4c(func_020b65c4(), o + 0x5c, 0);
                }
            }
        }
        return func_02003348(kind, self, 0, 0, data_ov004_022595c0);
    }
    return 0;
}
