/* func_ov003_022284a8 @ 0x022284a8, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern char data_ov003_0225f76c[];
extern void func_ov003_02228d48(char *self, int i);
extern void func_0209d200(void *a, void *b);
extern void func_020044a0(void *e);
extern void func_02004280(void *e);
extern void func_020e9898(void *p);
extern void func_0209d138(void *p);
extern void func_ov003_02228cd4(char *self);

void func_ov003_022284a8(char *self)
{
    int flag;
    char *e;
    int i;
    flag = 0;
    e = data_ov003_0225f76c;
    for (i = 0; i < 6; i++) {
        if (*(u8 *) (e + 0x7f)) {
            flag = 1;
        }
        func_ov003_02228d48(self, i);
        func_0209d200(self + 0x50, e + 0x7c);
        func_020044a0(e);
        func_02004280(e + 0x40);
        e += 0x24c;
    }
    func_020e9898(*(void **) (self + 0x80));
    func_0209d138(self + 0x50);
    if (flag) {
        func_ov003_02228cd4(self);
    }
    func_0209d138(self + 0x68);
}
