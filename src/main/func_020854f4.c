/* func_020854f4 @ 0x020854f4, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_02084b54(void);
extern void func_02084dac(void *a);
extern void func_0207921c(void);
extern int func_020b6660(void);
extern void func_0207be8c(void *a);
extern int func_020b5e70(void);
extern int func_020b6694(int a);
extern int func_0207cd4c(void *a, signed char b);
extern int func_0208150c(int a);
extern int func_02003704(int a);
extern void func_0207f454(int a);

extern u8 data_020e1ca8;
extern u8 data_021e5a2c[];

int func_020854f4(void)
{
    u8 *p;
    int v, w;
    func_02084b54();
    func_02084dac(&data_020e1ca8);
    func_0207921c();
    if (func_020b6660()) {
        p = data_021e5a2c;
        func_0207be8c(p);
        v = func_020b5e70();
        if (func_020b6694(v)) {
            w = func_0207cd4c(p, (signed char) v);
            if (w) {
                if (func_02003704(func_0208150c(w))) {
                    func_0207f454(w);
                }
            }
        }
    }
    return 1;
}
