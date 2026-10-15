/* func_ov004_0223232c @ 0x0223232c, 0x84 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b, c;
} Cfg;
extern u8 func_020b65c4(void);
extern void __register_global_object(Cfg *, void *destructor, void *);
extern void func_020012dc(void *object);
extern int func_020321bc(void *, int, int, int, Cfg *, int, int);
extern int data_ov004_022589f0;
extern Cfg data_ov004_02258a54;
extern char data_ov004_02258a48;
extern int data_020ca0f0;

void func_ov004_0223232c(char *self)
{
    if (func_020b65c4() == 0xa) {
        if ((data_ov004_022589f0 & 1) == 0) {
            data_ov004_02258a54.a = 0xe000;
            data_ov004_02258a54.b = 0;
            data_ov004_02258a54.c = data_020ca0f0 + 0x1000;
            __register_global_object(&data_ov004_02258a54, ((void *) &func_020012dc), &data_ov004_02258a48);
            data_ov004_022589f0 |= 1;
        }
        func_020321bc(self, 0x8000, 0x2000, 0x1000, &data_ov004_02258a54, 0, 0);
    }
}
