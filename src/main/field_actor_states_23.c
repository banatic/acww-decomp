/* field_actor_states_23: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0200c7d0 @ 0x0200c7d0, 0x3c bytes, Thumb
 * func_0200c708 @ 0x0200c708, 0xc8 bytes, Thumb
 */

#include "types.h"

extern void func_0200c89c(void *param1, void *param2, void *param3, void *param4);
extern int func_0200c904(void *param1, unsigned short param2, unsigned char param3, unsigned char param4, int param5,
                         void *param6);

// Sibling of func_0200c4cc, which supplied every callee prototype.

extern void *data_020ccf94;
extern void func_0200c610(void *p);
extern void func_0200c5e0(void *p);
extern void func_0200c598(void *p);
extern void *func_020984fc(u32 v);
extern void func_02099740(void *p, int n);
extern void *func_0209984c(void *p);
extern int func_0205dc94(void *p, void *v);
extern void func_02010934(void *p);
extern void func_02079280(void);
extern int func_02073908(void *p, u32 v);
extern void func_0200f164(void *receiver);
extern void func_0200f1a4(void *p, int n, u16 h);

void func_0200c7d0(void *param1, void *param2)
{
    unsigned char stack[3];
    void *r5 = param1;
    void *r4 = param2;

    func_0200c89c((char *) r5 + 0x8f0, &stack[2], &stack[0], &stack[1]);
    func_0200c904(r5, *(unsigned short *) &stack[2], stack[0], stack[1], 6, r4);
}

void func_0200c708(u8 *self)
{
    u8 *s = self + 0x7d4;
    void *p;
    int v;

    if (*(u8 *) (s + 0xc) == 0) {
        switch (*(u32 *) (s + 4)) {
            case 0:
                func_0200c610(self);
                break;
            case 1:
                func_0200c5e0(self);
                break;
            case 2:
                func_0200c598(self);
                break;
            case 3:
                p = func_020984fc(*(u32 *) (self + 0x800));
                if (p != 0) {
                    func_02099740(p, 0);
                    func_0205dc94(self + 0x70d, func_0209984c(p));
                    func_02010934(self);
                    func_02079280();
                }
                break;
        }
    }
    if (func_02073908(data_020ccf94, *(u32 *) (self + 0x800)) == 0) {
        return;
    }
    switch (*(u32 *) (s + 4)) {
        case 0:
            v = 0;
            break;
        case 1:
            v = 1;
            break;
        case 2:
            v = 2;
            break;
        case 3:
            func_0200f164(self);
            return;
        default:
            return;
    }
    func_0200f1a4(self, v, *(u16 *) s);
}
