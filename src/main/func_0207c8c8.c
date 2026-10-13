/* func_0207c8c8 @ 0x0207c8c8, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void MI_CpuFill8(void *p, int c, unsigned int n);
extern int func_0207caa0(int i, void *set);
extern u8 *func_02082500(unsigned char i);
extern void func_0207ca74(void *set, unsigned char i);
extern int func_0208150c(void *p);
extern int func_02003704(int t);
extern unsigned char func_02003648(int t);
extern void func_0207ca48(void *self, void *set, int v);
extern int func_020644cc(int n);

extern unsigned int data_021d12c8[5];

int func_0207c8c8(char *self, int kind, int flag)
{
    int count;
    int i;
    char *p;
    void *own;
    u8 *e;
    int t;
    int v;
    int sel;

    count = 0;
    own = self + 0x4060;
    MI_CpuFill8(data_021d12c8, count, 0x14);

    for (i = 0; i < 0x96; i++) {
        if (func_0207caa0((unsigned char) i, own) == 0) {
            e = func_02082500((unsigned char) i);
            if (e[0x4b] < 2) {
                if (flag == 0 || e[0x4b] == 0) {
                    if (e[0x4a] == kind) {
                        func_0207ca74(data_021d12c8, (unsigned char) i);
                        count++;
                    }
                }
            }
        }
    }

    if (count > 0) {
        p = self;
        for (i = 0; i < 8; i++) {
            t = func_0208150c(p);
            if (func_02003704(t) != 0) {
                v = func_02003648(t);
                if (func_0207caa0(v, data_021d12c8) != 0) {
                    func_0207ca48(self, data_021d12c8, v);
                    if (--count == 0) {
                        goto pick;
                    }
                }
            }
            p += 0x7ec;
        }
    }

pick:
    if (count > 0) {
        sel = func_020644cc(count);
        for (i = 0; i < 0x96; i++) {
            if (func_0207caa0((unsigned char) i, data_021d12c8) != 0) {
                if (sel == 0) {
                    return i;
                }
                sel--;
            }
        }
    }
    return -1;
}
